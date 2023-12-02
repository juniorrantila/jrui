#pragma once
#include "View.h"
#include <Ty/Base.h>

namespace UI {

struct Text : View<Text> {
    Text(c_string text)
        : m_text(text) 
    {
    }

    virtual c_string view_name() const override { return "Text"; }

    c_string text() const { return m_text; }
    Text& set_text(c_string text)
    {
        m_text = text;
        return *this;
    }

    Text& operator=(c_string text)
    {
        set_text(text);
        return *this;
    }

    operator c_string() { return m_text; }

    virtual void parse_item(TreeGen&) const override;

private:
    c_string m_text { "" };
};

}
