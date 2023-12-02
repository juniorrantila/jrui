#pragma once
#include "Stack.h"

namespace UI {

Stack HStack(Vector<ViewRef>&& subviews);

template <typename...Ts>
static Stack HStack(Ts... subviews)
{
    return HStack({
        subviews...
    });
}

}
