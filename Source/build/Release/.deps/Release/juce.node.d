cmd_Release/juce.node := c++ -bundle -undefined dynamic_lookup -Wl,-search_paths_first -mmacosx-version-min=10.5 -arch x86_64 -L./Release  -o Release/juce.node Release/obj.target/juce/NodeEntry.o 
