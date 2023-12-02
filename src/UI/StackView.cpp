#include "Stack.h"

namespace UI {

void Stack::parse_item(TreeGen& parser) const {
    c_string name = axis() == Axis::horizontal ? "HStack" : "VStack";
    if (m_subviews.empty()) {
        parser.debug("%s[]", name);
        return;
    }
    parser.debug("%s[", name);
    parser.push();
    for (auto const& view : m_subviews) {
        view->parse_item(parser);
    }
    parser.pop();
    parser.debug("]");
}

}
