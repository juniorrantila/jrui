#pragma once
#include <Cocoa/Cocoa.h>
#include <WebKit/WebKit.h>

@interface WVEngine : NSObject
@property (nonatomic, strong) WKWebView* webview;
@property (nonatomic, strong) NSWindow* window;
@property (nonatomic, strong) WKUserContentController* manager;
@property BOOL debug;

@property (copy) void(^messageHandler)(NSString*);

+(instancetype)withDebug:(BOOL)debug
               onMessage:(void(^)(NSString*))messageHandler;
+(BOOL)isAppBundled;

-(void)terminate;
-(void)run;
-(void)dispatch:(void(^)(void))block;
-(void)setTitle:(NSString*)title;
-(void)setSize:(int)width
        height:(int)height
        hints:(int)hints;
-(void)navigate:(NSURL*)url;
-(void)init:(NSString*)js;
-(void)eval:(NSString*)js;
-(void)onMessage:(NSString*)message;
-(void)applicationDidFinishLaunching:(id)sender
                                 app:(id)app;
-(void)setHTML:(NSString*)html;

@end
