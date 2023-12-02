#include "WVAppDelegate.h"
#include <objc/runtime.h>

@implementation WVAppDelegate 
@synthesize touchBar;

+(instancetype)withEngine:(WVEngine*)engine
{
    auto* instance = [self new];
    instance.engine = engine;
    return instance;
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)_sender {
    return TRUE;
}

-(void)applicationDidFinishLaunching:(NSNotification *)notification {
    id app = [notification object];
    [self.engine applicationDidFinishLaunching:self app:app];
}

@end
