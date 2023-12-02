#pragma once

namespace Ty {

template <typename Self>
struct Selfish {
    Self& self() { return *(Self*)this; }
    Self const& self() const { return *(Self*)this; }
};

}

using Ty::Selfish;
