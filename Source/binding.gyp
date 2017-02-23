{
  "targets": [
    {
      "target_name": "juce",
      "sources": [ "NodeEntry.cpp", "NativeEmitter.cpp" ],
      "include_dirs" : [
          "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}