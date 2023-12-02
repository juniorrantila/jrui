#include "Window.h"
#include "HTMLTreeGen.h"
#include "Controller.h"
#include <WV/WebView.h>
#include <WV/webview-c.h>

namespace UI {

void Window::run() const
{
    auto gen = UI::HTMLTreeGen();
    m_controller->body()->parse(gen);

    auto webview = WV::WebView(false);
    webview.set_size((int)m_min_width, (int)m_min_height, WEBVIEW_HINT_MIN);
    webview.set_size((int)m_min_width, (int)m_min_height, WEBVIEW_HINT_NONE);

    webview.set_html([NSString stringWithUTF8String:gen.rendered()]);
    webview.run();
}

}
