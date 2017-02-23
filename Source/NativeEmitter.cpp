//
//  NativeEmitter.cpp
//  binding
//
//  Created by Jen Fong Chao on 23/02/2017.
//
//

#include <node.h>
#include <iostream>
#include "NativeEmitter.h"

NativeEmitter *NativeEmitter::emitter = 0;

NativeEmitter::NativeEmitter() {};
NativeEmitter::~NativeEmitter()
{
    if (emit != nullptr) {
        delete emit;
    }
};

Nan::Persistent<v8::Function> NativeEmitter::constructor;
void NativeEmitter::Init(v8::Local<v8::Object> exports)
{
    Nan::HandleScope scope;
    
    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("NativeEmitter").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);
    
    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("NativeEmitter").ToLocalChecked(), tpl->GetFunction());
}

void NativeEmitter::New(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
    if (!info.IsConstructCall()) {
        return Nan::ThrowError("`new` required");
    }
    NativeEmitter* obj = instance();
    obj->Wrap(info.This());
    //  "access" emit function inherited from EventNativeEmitter
    obj->emit = new Nan::Callback(
                                  v8::Local<v8::Function>::Cast(obj->handle()->Get(Nan::New("emit").ToLocalChecked())));
    info.GetReturnValue().Set(info.This());
}

void NativeEmitter::onNotify(std::string eventName)
{
    NativeEmitter *obj = instance();
    v8::Local<v8::Value> argv[] = { Nan::New(eventName).ToLocalChecked() };
    obj->emit->Call(obj->handle(), 1, argv);
}

NativeEmitter* NativeEmitter::instance()
{
    if (!emitter) {
        emitter = new NativeEmitter();
    }
    return emitter;
}
