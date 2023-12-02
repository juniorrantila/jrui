#include "TreeGen.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

namespace UI {

[[gnu::format(printf, 2, 3)]] 
void TreeGen::debug(c_string fmt, ...) const // NOLINT(cert-dcl50-cpp)
{
    if (!debug())
        return;

    va_list args;
    va_start(args, fmt);

    if (!m_last_was_same_line) {
        for (usize i = 0; i < m_indent; i++) {
            printf("  ");
        }
    }
    vprintf(fmt, args); 
    printf("\n");
    m_last_was_same_line = false;

    va_end(args);
}

[[gnu::format(printf, 2, 3)]] 
void TreeGen::debugnl(c_string fmt, ...) const // NOLINT(cert-dcl50-cpp)
{
    if (!debug())
        return;

    va_list args;
    va_start(args, fmt);

    if (!m_last_was_same_line) {
        for (usize i = 0; i < m_indent; i++) {
            printf("  ");
        }
    }
    vprintf(fmt, args); 
    printf(" ");
    m_last_was_same_line = true;

    va_end(args);
}

[[gnu::format(printf, 2, 3)]] 
c_string TreeGen::fmt(c_string fmt, ...) const // NOLINT(cert-dcl50-cpp)
{
    va_list args;
    va_start(args, fmt);

    char* indent = nullptr;
    if (!m_last_was_same_line) {
        char* items = (char*)calloc(m_indent, 2);
        assert(items);
        memset(items, ' ', m_indent * 2);
        indent = items;
    }
    char* message = nullptr;
    assert(vasprintf(&message, fmt, args) != -1);
    char* complete_message= nullptr;
    assert(asprintf(&complete_message, "%s%s\n", indent, message) != -1);
    free(indent);
    free(message);

    m_last_was_same_line = false;

    va_end(args);

    return complete_message;
}

[[gnu::format(printf, 2, 3)]] 
c_string TreeGen::fmtnl(c_string fmt, ...) const // NOLINT(cert-dcl50-cpp)
{
    va_list args;
    va_start(args, fmt);

    char* indent = nullptr;
    if (!m_last_was_same_line) {
        char* items = (char*)calloc(m_indent, 2);
        assert(items);
        memset(items, ' ', m_indent * 2);
        indent = items;
    }
    char* message = nullptr;
    assert(vasprintf(&message, fmt, args) != -1);
    char* complete_message= nullptr;
    assert(asprintf(&complete_message, "%s%s ", indent, message) != -1);
    free(indent);
    free(message);

    m_last_was_same_line = false;

    va_end(args);

    return complete_message;
}

void TreeGen::reset()
{
    m_indent = 0;
    m_last_was_same_line = false;
}

void TreeGen::text(c_string content)
{
    if (content) {
        debugnl("'%s'", content);
    } else {
        debugnl("nil");
    }
    auto* context = start_text(content);
    end_text(context);
    debug("");
}

}
