#pragma once
#include "Base.h"

namespace Ty {

template <typename T>
struct Box {
    usize ref_count() const { return m_outline->ref_count; }

protected:

    template <typename... Args>
    Box(Args... args)
        : m_outline(new Outline(args...))
    {
    }

    Box(Box const& other)
        : m_outline(other.m_outline)
    {
        m_outline->inc_ref();
    }

    ~Box()
    {
        m_outline->dec_ref();
        if (ref_count() == 0) {
            // delete m_outline;
            m_outline = 0;
        }
    }

    Box& operator=(Box const& other)
    {
        if (this == &other)
            return *this;
        if (m_outline)
            ~Box();
        m_outline = other.m_outline;
        return *this;
    }

    auto* operator->() { return inner(); }
    auto const* operator->() const { return inner(); }

    struct Outline {
        typename T::Inner inner;
        usize ref_count { 0 };

        Outline()
            : ref_count(1)
        {
        }

        void inc_ref()
        {
            ref_count++;
        }

        void dec_ref()
        {
            if (ref_count <= 0)
                return;
            ref_count--;
            if (ref_count == 0) {
                inner.~Inner();
            }
        }
    };

    auto const* inner() const { return &m_outline->inner; }
    auto* inner() { return &m_outline->inner; }

private:
    Outline* m_outline { nullptr };
};

}

template <typename T>
using Box = Ty::Box<T>;
