#ifndef GC_INFO_EVENT_H_
#define GC_INFO_EVENT_H_

#include <nan.h>

namespace disa
{
    class Event : public Nan::AsyncResource
    {
    public:
        Event(v8::Local<v8::Function> callback);
        ~Event();

        Nan::Persistent<v8::Function> callback;
    };
} // namespace disa

#endif // GC_INFO_EVENT_H_
