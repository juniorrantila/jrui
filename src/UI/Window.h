#pragma once
#include "Forward.h"

namespace UI {

struct Window {
    Window() = default;

    Window controller(UI::Controller& controller)&&
    {
        m_controller = &controller;
        return *this;
    }

    Window min_size(usize width, usize height)&&
    {
        m_min_width = width;
        m_min_height = height;
        return *this;
    }

    void run() const;

private:
    UI::Controller* m_controller { nullptr };
    usize m_min_width { 0 };
    usize m_min_height { 0 };
};

}
