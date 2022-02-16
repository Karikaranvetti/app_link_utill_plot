 

{
  "targets": [
    {
      "target_name": "app_plot",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
       "libraries": ["-L/usr/local/lib",'-lzmq'],
      "sources": ["cc_source/app_plot.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}

