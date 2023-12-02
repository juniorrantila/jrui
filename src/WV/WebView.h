#pragma once
#include "WVEngine.h"
#include "WVJson.h"
#include <Foundation/Foundation.h>

namespace WV {

struct WebView {
    WebView(bool debug);

    static bool is_app_bundled();

    // FIXME: Make this return ErrorOr
    void bind(NSString* name, Json(^callback)(NSArray*)) const;
    void bind(NSString* name, void (^callback)(NSString*, NSString*)) const;
    void unbind(NSString* name) const;

    void resolve(NSString* seq, NSString* result, NSString* method = @"resolve") const;
    void reject(NSString* seq, NSString* result) const;

    void* window() const;
    void terminate() const;
    void run() const;
    void dispatch(void(^)(void)) const;
    void set_title(NSString* title) const;
    void set_size(int width, int height, int hints) const;
    void navigate(NSURL* url) const;
    void set_html(NSString* html) const;
    void init(NSString* js) const;
    void eval(NSString* js) const;

    void on_message(NSString* msg) const;
    void on_application_did_finish_launching(id, id app) const;

private:

    WVEngine* m_engine;
    NSMutableDictionary<NSString*, void(^)(NSString*, NSString*)>* m_bindings;
};

}
