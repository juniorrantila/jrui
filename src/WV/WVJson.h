#pragma once
#include <Foundation/Foundation.h>

namespace WV {

struct Json {
    Json(NSString* value)
        : m_value(value)
    {
    }

    Json(NSNumber* value)
        : m_value(value)
    {
    }

    Json(NSArray* value)
        : m_value(value)
    {
    }

    Json(NSNull*)
        : m_value(nil)
    {
    }

    Json(NSDictionary* value)
        : m_value(value)
    {
    }

    Json(BOOL value)
        : m_value(value == YES ? s_true : s_false)
    {
    }

    NSString* to_string() const;

private:
    static NSObject* s_true; 
    static NSObject* s_false;

    NSObject* m_value { nil };
};

}
