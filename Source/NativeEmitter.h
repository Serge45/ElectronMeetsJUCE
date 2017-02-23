//
//  Emitter.hpp
//  binding
//
//  Created by Raymond Chao on 23/02/2017.
//
//

#ifndef NATIVE_EMITTER_H
#define NATIVE_EMITTER_H

#include <nan.h>

class NativeEmitter : public Nan::ObjectWrap {
public:
    Nan::Callback* emit = nullptr;
    static void Init(v8::Local<v8::Object> exports);
    static void onNotify(std::string eventName);
private:
    NativeEmitter();
    ~NativeEmitter();
    static NativeEmitter *instance();
    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static Nan::Persistent<v8::Function> constructor;
    static NativeEmitter *emitter;
};

#endif // NATIVE_EMITTER_H
