#include "WVScriptMessageHandler.h"

@implementation WVScriptMessageHandler

+(instancetype)withEngine:(WVEngine*)engine {
    auto* instance = [self new];
    instance.engine = engine;
    return instance;
}

-(void)userContentController:(WKUserContentController *)userContentController didReceiveScriptMessage:(WKScriptMessage *)message {
    [self.engine onMessage:message.body];
}

@end
