{
  "targets": [
    {
      "target_name": "juce",
      "sources": [ "NodeEntry.cpp", 
                   "NativeEmitter.cpp",
                   "../JuceLibraryCode/juce_audio_basics.cpp",
                   "../JuceLibraryCode/juce_audio_devices.cpp",
                   "../JuceLibraryCode/juce_audio_formats.cpp",
                   "../JuceLibraryCode/juce_audio_processors.cpp",
                   "../JuceLibraryCode/juce_audio_utils.cpp",
                   "../JuceLibraryCode/juce_core.cpp",
                   "../JuceLibraryCode/juce_cryptography.cpp",
                   "../JuceLibraryCode/juce_data_structures.cpp",
                   "../JuceLibraryCode/juce_events.cpp",
                   "../JuceLibraryCode/juce_graphics.cpp",
                   "../JuceLibraryCode/juce_gui_basics.cpp",
                   "../JuceLibraryCode/juce_gui_extra.cpp",
                   "../JuceLibraryCode/juce_opengl.cpp",
                   "../JuceLibraryCode/juce_video.cpp",
                    ],
      "include_dirs" : [
          "<!(node -e \"require('nan')\")",
          "../include/node",
          "../JuceLibraryCode",
          "../JUCE/modules",
      ]
    }
  ]
}