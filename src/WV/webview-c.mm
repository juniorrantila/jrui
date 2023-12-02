/*
 * MIT License
 *
 * Copyright (c) 2017 Serge Zaitsev
 * Copyright (c) 2022 Steffen André Langnes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "webview-c.h"

#include "WebView.h"

extern "C" {

webview_t webview_create(int debug)
{
    auto* w = new WV::WebView((bool)debug);
    if (!w->window()) {
        delete w;
        return nullptr;
    }
    return w;
}

void webview_destroy(webview_t w) { delete static_cast<WV::WebView*>(w); }

void webview_run(webview_t w) { static_cast<WV::WebView*>(w)->run(); }

void webview_terminate(webview_t w) { static_cast<WV::WebView*>(w)->terminate(); }

void webview_dispatch(webview_t w, void (*fn)(webview_t, void*), void* arg)
{
    static_cast<WV::WebView*>(w)->dispatch([=]() {
        fn(w, arg);
    });
}

void webview_set_title(webview_t w, char const* title)
{
    static_cast<WV::WebView*>(w)->set_title([NSString stringWithUTF8String:title]);
}

void webview_set_size(webview_t w, int width, int height, int hints)
{
    static_cast<WV::WebView*>(w)->set_size(width, height, hints);
}

void webview_navigate(webview_t w, char const* url)
{
    if (!url || strlen(url) == 0)
        url = "about:blank";
    auto nsurl = [NSURL URLWithString:[NSString stringWithUTF8String:url]];
    static_cast<WV::WebView*>(w)->navigate(nsurl);
}

void webview_set_html(webview_t w, char const* html)
{
    static_cast<WV::WebView*>(w)->set_html([NSString stringWithUTF8String:html]);
}

void webview_init(webview_t w, char const* js)
{
    static_cast<WV::WebView*>(w)->init([NSString stringWithUTF8String:js]);
}

void webview_eval(webview_t w, char const* js)
{
    static_cast<WV::WebView*>(w)->eval([NSString stringWithUTF8String:js]);
}

void webview_bind(webview_t w, char const* name,
    void (*callback)(char const* seq, char const* arg, void* ctx), void* ctx)
{
    static_cast<WV::WebView*>(w)->bind([NSString stringWithUTF8String:name],
        [=](NSString* seq, NSString* arg) {
            callback(seq.UTF8String, arg.UTF8String, ctx);
        });
}

void webview_unbind(webview_t w, char const* name)
{
    static_cast<WV::WebView*>(w)->unbind([NSString stringWithUTF8String:name]);
}

void webview_return(webview_t w, char const* seq, int status, char const* result)
{
    static_cast<WV::WebView*>(w)->resolve([NSString stringWithUTF8String:seq],
        [NSString stringWithUTF8String:result], status == 0 ? @"resolve" : @"reject");
}
}
