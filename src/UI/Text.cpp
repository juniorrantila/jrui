#include "Forward.h"

#include "Text.h"
#include "TreeGen.h"

namespace UI {

void Text::parse_item(TreeGen& parser) const
{
    super::parse_item(parser);
    parser.text(m_text);
}

}
