#include "event.h"

#include <nan.h>

apio::Event::Event(v8::Local<v8::Function> callback)
    : Nan::AsyncResource("Event")
{
  this->callback.Reset(callback);
}

apio::Event::~Event()
{
  this->callback.Reset();
}
