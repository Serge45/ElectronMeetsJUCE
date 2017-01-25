/*
  ==============================================================================

    NodeEntry.cpp
    Created: 24 Jan 2017 1:44:48am
    Author: Serge Lu 

  ==============================================================================
*/

#include <memory>
#include <string>
#include <node.h>
#include "JuceHeader.h"

namespace demo {
    namespace {
        class LoopThroughAudioCallback : public juce::AudioIODeviceCallback {
            
            void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples) override {
                
                for (int j = 0; j < numOutputChannels; ++j) {
                    memcpy(outputChannelData[j], inputChannelData[0], sizeof(float) * numSamples);
                }
                
            }

            void audioDeviceAboutToStart (AudioIODevice* device) override {
                
            }


            void audioDeviceStopped() override {
                
            }
        };
    }

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
    
std::unique_ptr<juce::AudioDeviceManager> deviceManager;

void printString(const FunctionCallbackInfo<Value>& args) {
    juce::String jString("Hello JUCE");
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, jString.toStdString().c_str()));
}
    
void playTestSound(const FunctionCallbackInfo<Value>& args) {
    deviceManager->playTestSound();
}
    
void getAllAudioDevices(const FunctionCallbackInfo<Value>& args) {
    juce::OwnedArray<juce::AudioIODeviceType> types;
    deviceManager->createAudioDeviceTypes(types);
    
    juce::String typeName = types[0]->getTypeName();
    types[0]->scanForDevices();
    juce::StringArray deviceNames = types[0]->getDeviceNames();
    
    v8::Local<v8::Array> returnHandle = v8::Array::New(args.GetIsolate());
    
    for (int j = 0; j < deviceNames.size(); ++j) {
        returnHandle->Set(j, String::NewFromUtf8(args.GetIsolate(), deviceNames[j].toStdString().c_str()));
    }
    
    args.GetReturnValue().Set(returnHandle);
}
    
void setAudioDevice(const FunctionCallbackInfo<Value>& args) {
    
    v8::String::Utf8Value devName(args[0]->ToString());
    std::string nativeDevName(*devName);
    
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager->getAudioDeviceSetup(setup);
    setup.outputDeviceName = juce::String(nativeDevName);
    deviceManager->setAudioDeviceSetup(setup, true);
}

void init(Local<Object> exports) {
    deviceManager = std::unique_ptr<juce::AudioDeviceManager>(new juce::AudioDeviceManager());
    deviceManager->initialise(2, 2, nullptr, true);
    deviceManager->addAudioCallback(new LoopThroughAudioCallback());
    NODE_SET_METHOD(exports, "printJUCEString", printString);
    NODE_SET_METHOD(exports, "playTestSound", playTestSound);
    NODE_SET_METHOD(exports, "getAllAudioDevices", getAllAudioDevices);
    NODE_SET_METHOD(exports, "setAudioDevice", setAudioDevice);
}

NODE_MODULE(juce, init)

}  // namespace demo
