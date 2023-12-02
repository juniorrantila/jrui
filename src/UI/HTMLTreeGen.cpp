#include "HTMLTreeGen.h"

#include "Alignment.h"
#include "Axis.h"
#include "Sizing.h"
#include "Spacing.h"

#include "Stack.h"

#include <stdio.h>
#include <assert.h>

namespace UI {

void HTMLTreeGen::reset()
{
    if (m_rendered) {
        free((void*)m_rendered);
        m_rendered = nullptr;
    }
}

static c_string starting_boilerplate = R"(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <meta name="description" content="" />
  <link rel="icon" href="favicon.png">
  <style>
  @font-face {
    font-family: system-ui;
    font-style: normal;
    font-weight: 300;
    src: local(".SFNSText-Light"),
         local(".HelveticaNeueDeskInterface-Light"),
         local(".LucidaGrandeUI"),
         local("Ubuntu Light"),
         local("Segoe UI Light"),
         local("Roboto-Light"),
         local("DroidSans"),
         local("Tahoma");
  }
  :root {
    --system-ui: 'system-ui', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol";
  }
  * {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    user-select: none;
    -webkit-user-select: none;
  }
  h1:hover, h2:hover, h3:hover, h4:hover, h5:hover, h6:hover, p:hover {
    cursor: default;
  }
  html {
    color: #FEFEFE;
    background-color: #1B1B1B;
  }
  body {
    font-family: var(--system-ui);
  }
  html, body {
    height: 100%;
  }
  *[sizing="fillArea"] {
    width: 100%;
    height: 100%;
  }
  *[sizing="fitContent"] {
    width: fit-content; 
    height: fit-content;
  }
  *[spacing="equalSpacing"] {
    justify-content: space-around;
  }
  *[alignment="start"] {
    align-items: flex-start;
  }
  *[alignment="center"] {
    align-items: center;
  }
  *[alignment="end"] {
    align-items: flex-end;
  }

  v-stack, h-stack {
    display: flex;
    justify-content: center;
    align-items: center;
  }
  v-stack {
    flex-direction: column;
  }
  h-stack {
    flex-direction: row;
  }
  </style>
</head>
<body>)";
void HTMLTreeGen::start()
{
    m_rendered = fmt("%s", starting_boilerplate);
}

static c_string finishing_boilerplate = "</body>\n</html>";
void HTMLTreeGen::finish()
{
    add_allocated_part(fmt("%s", finishing_boilerplate));
}

HTMLTreeGen::TextContext* HTMLTreeGen::start_text(c_string content)
{
    add_allocated_part(fmt("<p>"));
    indented([&] {
        add_allocated_part(fmt("%s", content));
    });
    return nullptr;
}

void HTMLTreeGen::end_text(TextContext*)
{
    add_allocated_part(fmt("</p>"));
}

HTMLTreeGen::StackContext* HTMLTreeGen::start_stack(StackProperties const& properties)
{
    c_string name = [properties] {
        using enum Axis;
        switch (properties.axis) {
        case horizontal: return "h-stack";
        case vertical: return "v-stack";
        }
    }();
    c_string alignment = [properties] {
        using enum Alignment;
        switch (properties.alignment) {
        case start: return "start";
        case center: return "center";
        case end: return "end";
        }
    }();
    c_string sizing = [properties] {
        using enum Sizing;
        switch (properties.sizing) {
        case fillArea: return "fillArea";
        case fitContent: return "fitContent";
        }
    }();
    c_string spacing = [properties] {
        using enum Spacing;
        switch (properties.spacing) {
        case fill: return "fill";
        case fillEqually: return "fillEqually";
        case fillProportionally: return "fillProportionally";
        case equalSpacing: return "equalSpacing";
        case equalCentering: return "equalCentering";
        }
    }();

    add_allocated_part(fmt("<%s alignment='%s' sizing='%s' spacing='%s'>",
        name, alignment, sizing, spacing));

    return (StackContext*)name;
}

void HTMLTreeGen::end_stack(StackContext* ctx)
{
    add_allocated_part(fmt("</%s>", (c_string)ctx));
}

void HTMLTreeGen::add_allocated_part(c_string part)
{
    char* result = nullptr;
    assert(asprintf(&result, "%s%s", m_rendered ?: "", part) != -1);
    if (m_rendered) {
        free((void*)m_rendered);
    }
    m_rendered = result;
    free((void*)part);
}

}
