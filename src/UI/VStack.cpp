#include "VStack.h"

namespace UI {

Stack VStack(Vector<ViewRef>&& subviews)
{
    return Stack(Axis::vertical, std::move(subviews));
}

}
