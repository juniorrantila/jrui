#pragma once
#include "TreeGen.h"

namespace UI {

struct HTMLTreeGen : TreeGen {

    c_string rendered() const { return m_rendered; }

private:
    virtual void reset() override;
    virtual void start() override;
    virtual void finish() override;

    virtual TextContext* start_text(c_string) override;
    virtual void end_text(TextContext*) override; 

    virtual StackContext* start_stack(StackProperties const&) override;
    virtual void end_stack(StackContext*) override;

    void add_allocated_part(c_string);

    c_string m_rendered { nullptr };
};


}
