#include "HStack.h"

namespace UI {

Stack HStack(Vector<ViewRef>&& subviews)
{
    return Stack(Axis::horizontal, std::move(subviews));
}

}
