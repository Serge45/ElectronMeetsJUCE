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
#include "NativeEmitter.h"

namespace demo {
    namespace {
        class LoopThroughAudioCallback : public juce::AudioIODeviceCallback {
        public:
            LoopThroughAudioCallback() {}
            ~LoopThroughAudioCallback() {}
            float getPeak() const noexcept { return m_peak; }
        private:

            void audioDeviceIOCallback (const float** inputChannelData,
                                        int numInputChannels,
                                        float** outputChannelData,
                                        int numOutputChannels,
                                        int numSamples) override {

                for (int j = 0; j < numOutputChannels; ++j) {
                    memcpy(outputChannelData[j], inputChannelData[0], sizeof(float) * numSamples);
                }

                auto p = std::max_element(inputChannelData[0], inputChannelData[0] + numSamples, [] (float lhs, float rhs) {
                    return std::abs(lhs) < std::abs(rhs);
                });

                m_peak = std::abs(*p);
            }

            void audioDeviceAboutToStart (juce::AudioIODevice* device) override {

            }

            void audioDeviceStopped() override {

            }

        private:
            float m_peak = 0.f;
        };
    }

using v8::FunctionCallbackInfo;
using v8::Handle;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

std::unique_ptr<juce::AudioDeviceManager> deviceManager;
LoopThroughAudioCallback *loopThroughCallback;

void printString(const FunctionCallbackInfo<Value>& args)
{
    juce::String jString("Hello JUCE");
    NativeEmitter::onNotify("foo");
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, jString.toStdString().c_str()));
}

void playTestSound(const FunctionCallbackInfo<Value>& args)
{
    deviceManager->playTestSound();
}

void setAudioDeviceType(const FunctionCallbackInfo<Value>& args)
{
    v8::String::Utf8Value deviceName(args[0]->ToString());
    deviceManager->setCurrentAudioDeviceType(juce::String::fromUTF8(*deviceName), true);
}

void getAllAudioDeviceTypes(const FunctionCallbackInfo<Value>& args)
{
    juce::OwnedArray<juce::AudioIODeviceType> types;
    deviceManager->createAudioDeviceTypes(types);

    v8::Local<v8::Array> returnHandle = v8::Array::New(args.GetIsolate());

    for (int i = 0; i < types.size(); ++i) {
        returnHandle->Set(i, String::NewFromUtf8(args.GetIsolate(), types[i]->getTypeName().toRawUTF8()));
    }

    args.GetReturnValue().Set(returnHandle);
}

void getAllAudioDevices(const FunctionCallbackInfo<Value>& args)
{
    auto typeName = deviceManager->getCurrentAudioDeviceType();
    const juce::OwnedArray<juce::AudioIODeviceType> &types = deviceManager->getAvailableDeviceTypes();
    juce::StringArray deviceNames;

    for (int i = 0; i < types.size(); ++i) {
        if (types[i]->getTypeName() == typeName) {
            deviceNames = types[i]->getDeviceNames();
            break;
        }
    }

    v8::Local<v8::Array> returnHandle = v8::Array::New(args.GetIsolate());

    for (int j = 0; j < deviceNames.size(); ++j) {
        returnHandle->Set(j, String::NewFromUtf8(args.GetIsolate(), deviceNames[j].toStdString().c_str()));
    }

    args.GetReturnValue().Set(returnHandle);
}

void setAudioDevice(const FunctionCallbackInfo<Value>& args)
{
    v8::String::Utf8Value deviceName(args[0]->ToString());
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    deviceManager->getAudioDeviceSetup(setup);
    setup.outputDeviceName = juce::String::fromUTF8(*deviceName);
    auto devErr = deviceManager->setAudioDeviceSetup(setup, true);
    args.GetReturnValue().Set(v8::String::NewFromUtf8(args.GetIsolate(), devErr.toUTF8()));
}

void getInputVolume(const FunctionCallbackInfo<Value>& args)
{
    args.GetReturnValue().Set(v8::Number::New(args.GetIsolate(), loopThroughCallback->getPeak()));
}

void init(Local<Object> exports)
{
    NativeEmitter::Init(exports);
    deviceManager = std::unique_ptr<juce::AudioDeviceManager>(new juce::AudioDeviceManager());
    deviceManager->initialise(2, 2, nullptr, true);
    loopThroughCallback = new LoopThroughAudioCallback();
    deviceManager->addAudioCallback(loopThroughCallback);
    NODE_SET_METHOD(exports, "printJUCEString", printString);
    NODE_SET_METHOD(exports, "playTestSound", playTestSound);
    NODE_SET_METHOD(exports, "getAllAudioDeviceTypes", getAllAudioDeviceTypes);
    NODE_SET_METHOD(exports, "setAudioDeviceType", setAudioDeviceType);
    NODE_SET_METHOD(exports, "getAllAudioDevices", getAllAudioDevices);
    NODE_SET_METHOD(exports, "setAudioDevice", setAudioDevice);
    NODE_SET_METHOD(exports, "getInputVolume", getInputVolume);
}

NODE_MODULE(juce, init)

}  // namespace demo
