ui_lib = library('ui', [
    'Text.cpp',
    'Stack.cpp',
    'VStack.cpp',
    'HStack.cpp',
    'View.cpp',
    'TreeGen.cpp',
    'HTMLTreeGen.cpp',
    'Window.mm',
  ], dependencies: [
    ty_dep,
    wv_dep,
    cocoa_dep,
  ])

ui_dep = declare_dependency(
  link_with: ui_lib,
  include_directories: '..'
  )
