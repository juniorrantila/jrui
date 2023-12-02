wv_lib = shared_library('wv', [
    'WebView.mm',
    'WVUIDelegate.mm',
    'WVAppDelegate.mm',
    'WVScriptMessageHandler.mm',
    'WVEngine.mm',
    'WVJson.mm',
    'webview-c.mm',
  ], dependencies: [
    cocoa_dep,
    webkit_dep,
    ty_dep,
  ])

wv_dep = declare_dependency(
  link_with: wv_lib,
  include_directories: '..'
  )
