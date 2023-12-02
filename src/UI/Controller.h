#pragma once
#include "Forward.h"

#include "Alignment.h"
#include "HStack.h"
#include "Sizing.h"
#include "Spacing.h"
#include "Text.h"
#include "VStack.h"
#include "View.h"

namespace UI {

struct Controller {
    virtual ViewRef body() = 0;

protected:
    using enum Alignment;
    using enum Sizing;
    using enum Spacing;

    static Stack HStack(Vector<ViewRef>&& subviews)
    {
        return UI::HStack(std::move(subviews));
    }

    static Stack VStack(Vector<ViewRef>&& subviews)
    {
        return UI::VStack(std::move(subviews));
    }


    template <typename...Ts>
    static Stack VStack(Ts... subviews)
    {
        return UI::VStack({
            subviews...
        });
    }

    template <typename...Ts>
    static Stack HStack(Ts... subviews)
    {
        return UI::HStack({
            subviews...
        });
    }

    static UI::Text Text(c_string const& text)
    {
        return UI::Text(text);
    }

    template <typename Case, typename F>
    static UI::ViewRef When(Case const& kase, F cb)
    {
        return cb(kase);
    }
};

}
