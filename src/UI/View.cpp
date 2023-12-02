#include "View.h"
#include "TreeGen.h"

namespace UI {

ViewBase::~ViewBase() 
{
}

void ViewBase::parse(TreeGen& parser) const
{
    parser.reset();
    parser.start();
    parse_item(parser);
    parser.finish();
}

void ViewBase::parse_item(TreeGen& parser) const
{
    parser.debugnl("%s", view_name());
}

}
