#include "WVJson.h"
#include <Foundation/Foundation.h>

namespace WV {

NSObject* Json::s_true = [[NSObject alloc] init];
NSObject* Json::s_false = [[NSObject alloc] init];

NSString* Json::to_string() const
{
    if (m_value == nil || [m_value isKindOfClass:[NSNull class]] == YES) {
        return @"null";
    }

    if ([m_value isKindOfClass:[NSString class]] == YES) {
        // FIXME: Escape this properly
        return [NSString stringWithFormat:@"\"%@\"", m_value];
    }

    if ([m_value isKindOfClass:[NSNumber class]] == YES) {
        return ((NSNumber*)m_value).stringValue;
    }

    if (m_value == s_true) {
        return @"true";
    }

    if (m_value == s_false) {
        return @"false";
    }

    if ([m_value isKindOfClass:[NSArray class]] == NO && [m_value isKindOfClass:[NSDictionary class]] == NO) {
        @throw [NSException exceptionWithName:@"invalid input" reason:@"excpected array or dictionary" userInfo:nil];
    }

    NSError* error = nil;
    auto* result_json = [NSJSONSerialization dataWithJSONObject:m_value options:0 error:&error];
    if (error != nil) {
        @throw error;
    }
    auto result = [[NSString alloc] initWithData:result_json encoding:NSUTF8StringEncoding];
    return result;
}

}
