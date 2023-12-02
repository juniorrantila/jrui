#pragma once
#include "Alignment.h"
#include "Axis.h"
#include "Sizing.h"
#include "Spacing.h"
#include "View.h"

#include <Ty/Array.h>
#include <Ty/Base.h>
#include <Ty/Vector.h>

namespace UI {

#define MAKE_GET_SET(Type, name)                    \
    Type name() const { return m_properties.name; } \
    Stack& name(Type name)                          \
    {                                               \
        m_properties.name = name;                   \
        return *this;                               \
    }

struct StackProperties {
    Axis axis;

    Alignment alignment { Alignment::center };
    Sizing sizing { Sizing::fillArea };
    Spacing spacing { Spacing::equalSpacing };
};

struct Stack : View<Stack> {
    Stack(Axis axis, Vector<ViewRef>&& subviews)
        : m_subviews(std::move(subviews))
    {
        m_properties.axis = axis;
    }

    virtual c_string view_name() const override;

    MAKE_GET_SET(Alignment, alignment);
    MAKE_GET_SET(Sizing, sizing);
    MAKE_GET_SET(Spacing, spacing);

    Axis axis() const { return m_properties.axis; }

    StackProperties const& properties() const { return m_properties; }

protected:
    virtual void parse_item(TreeGen&) const override;

private:
    Vector<ViewRef> m_subviews {};
    StackProperties m_properties {};
};

#undef MAKE_GET_SET

}
