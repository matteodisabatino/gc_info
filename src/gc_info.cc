#include <algorithm>
#include <chrono>
#include <vector>

#include <nan.h>

#include "event.h"
#include "heap_stats.h"
#include "gc_stats.h"

static apio::GCStats gc_stats;
static std::vector<apio::Event *> on_data_callbacks;

static void StopHandle(uv_handle_t *handle_info)
{
  delete handle_info;
}

static void StartHandle(uv_async_t *handle_info)
{
  Nan::HandleScope scope;

  apio::GCStats *data = static_cast<apio::GCStats *>(handle_info->data);
  apio::HeapStats pre_stats = data->pre_stats();
  apio::HeapStats post_stats = data->post_stats();
  apio::HeapStats diff_stats = post_stats - pre_stats;
  data->set_diff_stats(diff_stats);

  v8::Local<v8::Object> obj = data->ToV8Object();
  v8::Local<v8::Value> arguments[] = {obj};

  for (apio::Event *event : on_data_callbacks)
  {
    Nan::Persistent<v8::Function> &persistent_callback = event->callback;
    v8::Local<v8::Function> callback = Nan::New(persistent_callback);
    v8::Local<v8::Object> target = Nan::New<v8::Object>();
    event->runInAsyncScope(target, callback, 1, arguments);
  }

  uv_close(reinterpret_cast<uv_handle_t *>(handle_info), StopHandle);
}

static NAN_GC_CALLBACK(OnGCEpilogue)
{
  uint64_t millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                                      std::chrono::system_clock::now().time_since_epoch())
                                      .count();
  gc_stats.set_ended_at(millisec_since_epoch);
  gc_stats.set_gctype(type);
  v8::HeapStatistics epilogueGCStats;
  Nan::GetHeapStatistics(&epilogueGCStats);
  gc_stats.set_post_stats(epilogueGCStats);

  uv_async_t *handle_info = new uv_async_t;
  handle_info->data = &gc_stats;
  uv_async_init(uv_default_loop(), handle_info, StartHandle);
  uv_async_send(handle_info);
}

static NAN_GC_CALLBACK(OnGCPrologue)
{
  uint64_t millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                                      std::chrono::system_clock::now().time_since_epoch())
                                      .count();
  gc_stats.set_started_at(millisec_since_epoch);
  v8::HeapStatistics prologueGCStats;
  Nan::GetHeapStatistics(&prologueGCStats);
  gc_stats.set_pre_stats(prologueGCStats);
}

static NAN_METHOD(On)
{
  if (info.Length() != 2)
  {
    return Nan::ThrowError("Two arguments are required");
  }

  if (!info[0]->IsString())
  {
    return Nan::ThrowError("First argument must be string");
  }

  if (!info[1]->IsFunction())
  {
    return Nan::ThrowError("Second argument must be function");
  }

  if (std::string(*Nan::Utf8String(info[0])) != "data")
  {
    return;
  }

  v8::Local<v8::Function> cb = Nan::To<v8::Function>(info[1]).ToLocalChecked();
  apio::Event *event = new apio::Event(cb);
  on_data_callbacks.push_back(event);

  Nan::AddGCEpilogueCallback(OnGCEpilogue);
}

static NAN_METHOD(Off)
{
  if (info.Length() == 0)
  {
    return Nan::ThrowError("At least one arguments is required");
  }

  if (!info[0]->IsString())
  {
    return Nan::ThrowError("First argument must be string");
  }

  if (!info[1]->IsUndefined() && !info[1]->IsFunction())
  {
    return Nan::ThrowError("Second argument must be undefined or function");
  }

  if (std::string(*Nan::Utf8String(info[0])) != "data")
  {
    return;
  }

  if (info[1]->IsFunction())
  {
    v8::Local<v8::Function> cb = Nan::To<v8::Function>(info[1]).ToLocalChecked();
    apio::Event *event = new apio::Event(cb);
    std::vector<apio::Event *>::iterator it = std::find_if(
        on_data_callbacks.begin(), on_data_callbacks.end(),
        [event](apio::Event *e) { return e->callback == event->callback; });

    if (it != on_data_callbacks.end())
    {
      on_data_callbacks.erase(it);
    }

    delete event;
    return;
  }

  for (apio::Event *e : on_data_callbacks)
  {
    delete e;
  }

  on_data_callbacks.clear();
}

NAN_MODULE_INIT(Init)
{
  Nan::HandleScope scope;
  Nan::AddGCPrologueCallback(OnGCPrologue);

  Nan::Set(target, Nan::New("on").ToLocalChecked(),
           Nan::GetFunction(
               Nan::New<v8::FunctionTemplate>(On))
               .ToLocalChecked());

  Nan::Set(target, Nan::New("off").ToLocalChecked(),
           Nan::GetFunction(
               Nan::New<v8::FunctionTemplate>(Off))
               .ToLocalChecked());
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
