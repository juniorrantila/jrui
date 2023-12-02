#pragma once
#include <Cocoa/Cocoa.h>
#include "WVEngine.h"

@interface WVAppDelegate : NSResponder<NSApplicationDelegate, NSTouchBarProvider>
@property (nonatomic, strong) WVEngine* engine;

+(instancetype)withEngine:(WVEngine*)engine;

@end
