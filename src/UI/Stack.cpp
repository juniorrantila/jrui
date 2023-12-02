#include "Stack.h"
#include "TreeGen.h"

namespace UI {

c_string Stack::view_name() const
{
    return axis() == Axis::horizontal ? "HStack" : "VStack";
}

void Stack::parse_item(TreeGen& parser) const {
    super::parse_item(parser);
    parser.stack(properties(), [&] {
        for (auto const& view : m_subviews) {
            view->parse_item(parser);
        }
    });
}

}
