#include "WVEngine.h"

#include "WVAppDelegate.h"
#include "WebView.h"
#include "WVScriptMessageHandler.h"
#include "WVUIDelegate.h"
#include "webview-c.h"

#include <WebKit/WebKit.h>

@implementation WVEngine
+(instancetype)withDebug:(BOOL)debug
                  onMessage:(void(^)(NSString*))messageHandler
{
    auto* instance = [self new];
    instance.debug = debug;
    instance.window = nil;
    instance.messageHandler = messageHandler;

    auto app = [NSApplication sharedApplication];
    app.delegate = [WVAppDelegate withEngine:instance];

    // Start the main run loop so that the app delegate gets the
    // NSApplicationDidFinishLaunchingNotification notification after the run
    // loop has started in order to perform further initialization.
    // We need to return from this constructor so this run loop is only
    // temporary.
    [app run];

    return instance;
}

+(BOOL)isAppBundled {
    auto bundle = [NSBundle mainBundle];
    if (!bundle)
        return NO;
    return [[bundle bundlePath] hasSuffix:@".app"];
}

-(void)terminate
{
    [NSApp terminate:nil];
}

-(void)run
{
    [NSApp run];
}

-(void)dispatch:(void(^)(void))block
{
    dispatch_async(dispatch_get_main_queue(), block);
}

-(void)setTitle:(NSString*)title
{
    [self.window setTitle:title];
}

-(void)setSize:(int)width
        height:(int)height
        hints:(int)hints
{
    auto style = static_cast<NSWindowStyleMask>(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable
        | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
        // | NSWindowStyleMaskFullSizeContentView // FIXME: This looks good, but can't move
        // window.
    );
    [self.window setStyleMask:style];

    if (hints == WEBVIEW_HINT_MIN) {
        [self.window setContentMinSize:CGSizeMake(width, height)];
    } else if (hints == WEBVIEW_HINT_MAX) {
        [self.window setContentMaxSize:CGSizeMake(width, height)];
    } else {
        [self.window setFrame:CGRectMake(0, 0, width, height) display:YES animate:NO];
    }
    [self.window center];
}

-(void)navigate:(NSURL*)url
{
    [self.webview loadRequest:[NSURLRequest requestWithURL:url]];
}

-(void)setHTML:(NSString*)html
{
    [self.webview loadHTMLString:html baseURL:nil];
}

-(void)init:(NSString*)js
{
    [self.manager addUserScript:[[WKUserScript alloc]
                 initWithSource:js
                  injectionTime:WKUserScriptInjectionTimeAtDocumentStart
               forMainFrameOnly:YES]];
}

-(void)eval:(NSString*)js
{
    [self.webview evaluateJavaScript:js completionHandler:nil];
}

-(void)onMessage:(NSString*)message
{
    self.messageHandler(message);
}

-(void)applicationDidFinishLaunching:(id)sender
                                 app:(id)app
{
    // See comments related to application lifecycle in create_app_delegate().
    if (!self.window) {
        // Stop the main run loop so that we can return
        // from the constructor.
        [app stop:nil];
    }

    // Activate the app if it is not bundled.
    // Bundled apps launched from Finder are activated automatically but
    // otherwise not. Activating the app even when it has been launched from
    // Finder does not seem to be harmful but calling this function is rarely
    // needed as proper activation is normally taken care of for us.
    // Bundled apps have a default activation policy of
    // NSApplicationActivationPolicyRegular while non-bundled apps have a
    // default activation policy of NSApplicationActivationPolicyProhibited.
    // if (self.debug == NO && WVEngine.isAppBundled == NO) {
      // "setActivationPolicy:" must be invoked before
      // "activateIgnoringOtherApps:" for activation to work.
      [app setActivationPolicy:NSApplicationActivationPolicyRegular];

      // Activate the app regardless of other active apps.
      // This can be obtrusive so we only do it when necessary.
      [app activateIgnoringOtherApps:YES];
    // }

    // Main window
    if (!self.window) {
        auto style = NSWindowStyleMaskTitled | NSWindowStyleMaskFullSizeContentView
            | NSWindowStyleMaskUnifiedTitleAndToolbar;
        self.window = [[NSWindow alloc] initWithContentRect:CGRectMake(0, 0, 0, 0) styleMask:style backing:NSBackingStoreBuffered defer:NO];

        // [window setToolbarStyle:NSWindowToolbarStyleUnified];
        [self.window setTitlebarAppearsTransparent:YES];
    }

    // Webview
    auto config = [WKWebViewConfiguration new];
    self.manager = [config userContentController];

    if (self.debug == YES) {
        [[config preferences] setValue:@YES forKey:@"developerExtrasEnabled"];
    }

    [[config preferences] setValue:@YES forKey:@"fullScreenEnabled"];
    [[config preferences] setValue:@YES forKey:@"javaScriptCanAccessClipboard"];
    [[config preferences] setValue:@YES forKey:@"DOMPasteAllowed"];

    auto* ui_delegate = [WVUIDelegate new];

    self.webview = [[WKWebView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) configuration:config];
    [self.webview setUIDelegate:ui_delegate];

    auto* script_message_handler = [WVScriptMessageHandler withEngine:self];
    [self.manager addScriptMessageHandler:script_message_handler name:@"external"];

    
    [self init:@R"(
      window.external = {
        invoke: function(s) {
          window.webkit.messageHandlers.external.postMessage(s);
        },
      };
    )"];

    [self.window setContentView:self.webview];
    [self.window makeKeyAndOrderFront:nil];
}

@end
