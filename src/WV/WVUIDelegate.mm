#import "WVUIDelegate.h"

@implementation WVUIDelegate

-(void)webView:(WKWebView *)webView runOpenPanelWithParameters:(WKOpenPanelParameters *)parameters
                                              initiatedByFrame:(WKFrameInfo *)frame
                                             completionHandler:(void (^)(NSArray<NSURL *> * _Nullable))completionHandler
{
        auto allows_multiple_selection = [parameters allowsMultipleSelection];
        auto allows_directories = [parameters allowsDirectories];

        // Show a panel for selecting files.
        auto panel = [NSOpenPanel openPanel];
        [panel setCanChooseFiles:YES];
        [panel setCanChooseDirectories:allows_directories];
        [panel setAllowsMultipleSelection:allows_multiple_selection];
        auto modal_response = [panel runModal];

        // Get the URLs for the selected files. If the modal was canceled
        // then we pass null to the completion handler to signify
        // cancellation.
        auto urls = modal_response == NSModalResponseOK ? [panel URLs] : nil;

        // Invoke the completion handler block.
        auto sig = [NSMethodSignature signatureWithObjCTypes:"v@?@"];
        auto invocation = [NSInvocation invocationWithMethodSignature:sig];
        [invocation setTarget:completionHandler];
        [invocation setArgument:&urls atIndex:1];
        [invocation invoke];
}

@end
