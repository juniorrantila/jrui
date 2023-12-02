#pragma once
#include <Cocoa/Cocoa.h>
#include <WebKit/WebKit.h>
#include "WVEngine.h"

@interface WVScriptMessageHandler : NSResponder<WKScriptMessageHandler>
@property (nonatomic, strong) WVEngine* engine;

+(instancetype)withEngine:(WVEngine*)engine;

@end
