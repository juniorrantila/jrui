#pragma once
#include "Base.h"
#include <array>

namespace Ty {

template <typename T, usize Size>
using Array = std::array<T, Size>;

}

using Ty::Array;
