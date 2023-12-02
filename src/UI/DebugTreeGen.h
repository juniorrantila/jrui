#pragma once
#include "TreeGen.h"

namespace UI {

struct DebugGen : TreeGen {
private:
    virtual TextContext* start_text(c_string) override { return nullptr; };
    virtual void end_text(TextContext*) override {};

    virtual StackContext* start_stack(StackProperties const&) override { return nullptr; }
    virtual void end_stack(StackContext*) override {}

    virtual c_string debug_start_token() const override { return "["; }
    virtual c_string debug_end_token() const override { return "]"; }

    virtual bool debug() const override { return true; }
};


}
