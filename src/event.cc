#include "event.h"

#include <nan.h>

disa::Event::Event(v8::Local<v8::Function> callback) : Nan::AsyncResource("Event")
{
    this->callback.Reset(callback);
}

disa::Event::~Event()
{
    this->callback.Reset();
}
