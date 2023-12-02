#pragma once
#include "Stack.h"

namespace UI {

Stack VStack(Vector<ViewRef>&& subviews);

template <typename...Ts>
static Stack VStack(Ts... subviews)
{
    return VStack({
        subviews...
    });
}

}
