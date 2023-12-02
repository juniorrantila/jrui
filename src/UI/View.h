#pragma once
#include "Forward.h"
#include <functional>

namespace UI {

struct ViewBase {
    virtual ~ViewBase();

    void parse(TreeGen&) const;

    virtual void on_click() {}

    virtual c_string view_name() const = 0;

    virtual void parse_item(TreeGen&) const;
};
using ViewRef = std::shared_ptr<ViewBase>;

template <typename Self>
struct View : public ViewBase {
    using super = ViewBase;

    Self& on_click(std::function<void(Self&)> cb)
    {
        m_onclick = cb;
        return self();
    }

    virtual void on_click() override final
    {
        if (m_onclick) {
            m_onclick(self());
        }
    }

    operator ViewRef()
    {
        return std::make_shared<Self>(self());
    }

private:
    Self& self() { return *(Self*)this; }
    Self const& self() const { return *(Self*)this; }

    std::function<void(Self&)> m_onclick { nullptr };
};

}
