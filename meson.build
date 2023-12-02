project('seashore', ['cpp', 'objcpp'],
  default_options: [
    # 'cpp_std=c++20', # Meson seems to be confused when objcpp is used.
    'warning_level=3',
    'default_library=static',
    'buildtype=release',
    # 'cpp_rtti=false', # Meson seems confused?
    'cpp_eh=none',
  ])

if not meson.is_subproject()
  add_global_arguments([
      '-Wno-c99-extensions',
      '-Wno-dollar-in-identifier-extension', 
      '-Wno-gnu-auto-type',
      '-Wno-gnu-case-range', 
      '-Wno-gnu-conditional-omitted-operand', 
      '-Wno-gnu-statement-expression', 
      '-Wno-gnu-zero-variadic-macro-arguments',
      '-Wno-user-defined-literals',
      '-Wno-keyword-macro',
      '-Werror=unused-result',
    ], language: ['objcpp', 'cpp'])

  # Since meson seems to get confused when objcpp is used in project.
  add_global_arguments('-std=c++20', language: ['objcpp', 'cpp'])

  add_global_arguments('-fobjc-arc', language: 'objcpp')
endif

cocoa_dep = dependency('cocoa')
webkit_dep = dependency('webkit')

subdir('src')
subdir('examples')
