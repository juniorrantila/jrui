#include "WebView.h"
#include <Foundation/Foundation.h>

namespace WV {

WebView::WebView(bool debug)
    : m_bindings([[NSMutableDictionary alloc] init])
{
    m_engine = [WVEngine withDebug:(BOOL)debug
                         onMessage:^(NSString* message) {
        this->on_message(message);
    }];
}

void WebView::bind(NSString* name, Json(^callback)(NSArray*)) const
{
    bind(name, [=](NSString* seq, NSString* arg) {
        NSError* error = nil;
        id json = [NSJSONSerialization JSONObjectWithData:[arg dataUsingEncoding:NSUTF8StringEncoding]
                                                              options:0 error:&error];
        assert(error == nil);
        assert([json isKindOfClass:[NSArray class]]);

        @try {
            resolve(seq, callback((NSArray*)json).to_string());
        } @catch(NSException* error) {
            reject(seq, [NSString stringWithFormat:@"\"%@\"", error]);
        }
    });
}

void WebView::bind(NSString* name, void (^callback)(NSString*, NSString*)) const
{
    if ([m_bindings valueForKey:name] != nil) {
        return;
    }

    [m_bindings setValue:callback forKey:name];
    auto js = [NSString stringWithFormat:@R"((() => {
        var name = '%@';
        var RPC = window._rpc = (window._rpc || {nextSeq: 1});
        window[name] = function() {
            var seq = RPC.nextSeq++;
            var promise = new Promise((resolve, reject) => {
                RPC[seq] = {
                    resolve: resolve,
                    reject: reject,
                };
            });
            window.external.invoke(JSON.stringify({
                id: seq,
                method: name,
                params: Array.prototype.slice.call(arguments),
            }));
            return promise;
        };
    })();)", name];
    init(js);
    eval(js);
}

void WebView::unbind(NSString* name) const
{
    if ([m_bindings valueForKey:name] == nil)
        return;
    [m_bindings setValue:nil forKey:name];
    auto js = [NSString stringWithFormat:@"delete window['%@'];", name];
    init(js);
    eval(js);
}

void WebView::resolve(NSString* seq, NSString* result, NSString* method) const
{
    dispatch([=]() {
        auto js = [NSString stringWithFormat:@R"(
            window._rpc[%@].%@(%@);
            delete window._rpc[%@];
        )", seq, method, result, seq];
        eval(js);
    });
}

void WebView::reject(NSString* seq, NSString* result) const
{
    resolve(seq, result, @"reject");
}


bool WebView::is_app_bundled()
{
    return [WVEngine isAppBundled] == YES;
}

void* WebView::window() const { return (__bridge void*)[m_engine window]; }

void WebView::terminate() const { [m_engine terminate]; }

void WebView::run() const { [m_engine run]; }

void WebView::dispatch(void(^func)(void)) const
{
    [m_engine dispatch:func];
}

void WebView::set_title(NSString* title) const
{
    [m_engine setTitle:title];
}

void WebView::set_size(int width, int height, int hints) const
{
    [m_engine setSize:width height:height hints:hints];
}

void WebView::navigate(NSURL* url) const
{
    [m_engine navigate:url];
}

void WebView::set_html(NSString* html) const
{
    [m_engine setHTML:html];
}

void WebView::init(NSString* js) const
{
    [m_engine init:js];
}

void WebView::eval(NSString* js) const
{
    [m_engine eval:js];
}

void WebView::on_application_did_finish_launching(id delegate, id app) const
{
    [m_engine applicationDidFinishLaunching:delegate app:app];
}

void WebView::on_message(NSString* msg) const
{
    auto* data = [NSData dataWithBytes:msg.UTF8String length:msg.length];
    NSError* error = nil;
    id json_object = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
    if (error) {
        NSLog(@"Error: %@ (%@)", error.userInfo.allValues[0], msg);
        return;
    }
    if ([json_object isKindOfClass:[NSDictionary class]] == NO)
        return;
    auto* dictionary = (NSDictionary*)json_object;

    id seq_id = [dictionary valueForKey:@"id"];
    if ([seq_id isKindOfClass:[NSNumber class]] == NO) {
        NSLog(@"expected number for id, got %@", [seq_id class]);
        return;
    }
    auto seq_number = (NSNumber*)seq_id;
    auto seq = seq_number.stringValue;

    id name_id = [dictionary valueForKey:@"method"];
    if ([name_id isKindOfClass:[NSString class]] == NO) {
        NSLog(@"expected string for method, got %@", [name_id class]);
        return;
    }
    auto name = (NSString*)(name_id);

    id args_id = [dictionary valueForKey:@"params"];
    if ([args_id isKindOfClass:[NSArray class]] == NO) {
        NSLog(@"expected array for args, got %@", [args_id class]);
        return;
    }
    auto* args_json = [NSJSONSerialization dataWithJSONObject:args_id options:0 error:nil];
    auto args = [[NSString alloc] initWithData:args_json encoding:NSUTF8StringEncoding];

    auto func = [m_bindings valueForKey:name];
    if (func == nil)
        return;
    func(seq, args);
}

}

