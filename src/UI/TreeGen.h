#pragma once
#include "Forward.h"
#include "View.h"

namespace UI {

struct TreeGen {
    [[gnu::format(printf, 2, 3)]] 
    void debug(c_string fmt, ...) const;

    [[gnu::format(printf, 2, 3)]] 
    void debugnl(c_string fmt, ...) const;

    [[gnu::format(printf, 2, 3)]] 
    [[nodiscard]] c_string fmt(c_string fmt, ...) const;

    [[gnu::format(printf, 2, 3)]] 
    [[nodiscard]] c_string fmtnl(c_string fmt, ...) const;

    virtual void reset();
    virtual void start() {}
    virtual void finish() {}

    template <typename F>
    void stack(StackProperties const& properties, F build)
    {
        auto* context = start_stack(properties);
        indented(build);
        end_stack(context);
    }

    template <typename F>
    void indented(F build)
    {
        push();
        build();
        pop();
    }

    void text(c_string content);

protected:
    usize indent() const { return m_indent; }

    struct StackContext;
    virtual StackContext* start_stack(StackProperties const&) = 0;
    virtual void end_stack(StackContext*) = 0;

    struct TextContext;
    virtual TextContext* start_text(c_string) = 0;
    virtual void end_text(TextContext*) = 0;

    virtual bool debug() const { return false; };

    virtual c_string debug_start_token() const { return nullptr; }
    virtual c_string debug_end_token() const { return nullptr; }

private:
    void push()
    {
        c_string token = debug_start_token();
        if (token)
            debug("%s", token);
        m_indent++;
    }

    void pop()
    {
        if (__builtin_sub_overflow(m_indent, 1, &m_indent))
            m_indent = 0;
        c_string token = debug_end_token();
        if (token)
            debug("%s", token);
    }

    usize m_indent { 0 };
    mutable bool m_last_was_same_line { false };
};

}
