#include "gc_stats.h"

#include <nan.h>

#include "heap_stats.h"

disa::GCStats::GCStats() {}

disa::GCStats::~GCStats() {}

v8::Local<v8::Object> disa::GCStats::ToV8Object()
{
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("startedAt").ToLocalChecked(),
           Nan::New<v8::Number>(this->started_at_));
  Nan::Set(obj, Nan::New("endedAt").ToLocalChecked(),
           Nan::New<v8::Number>(this->ended_at_));
  Nan::Set(obj, Nan::New("duration").ToLocalChecked(),
           Nan::New<v8::Number>(this->ended_at_ - this->started_at_));
  Nan::Set(obj, Nan::New("gctype").ToLocalChecked(),
           Nan::New<v8::Number>(this->gctype_));
  Nan::Set(obj, Nan::New("pre").ToLocalChecked(),
           this->pre_stats_.ToV8Object());
  Nan::Set(obj, Nan::New("post").ToLocalChecked(),
           this->post_stats_.ToV8Object());
  Nan::Set(obj, Nan::New("diff").ToLocalChecked(),
           this->diff_stats_.ToV8Object());

  return obj;
}

disa::HeapStats disa::GCStats::pre_stats()
{
  return this->pre_stats_;
}

void disa::GCStats::set_pre_stats(v8::HeapStatistics &pre_stats)
{
  this->pre_stats_ = disa::HeapStats(pre_stats);
}

disa::HeapStats disa::GCStats::post_stats()
{
  return this->post_stats_;
}

void disa::GCStats::set_post_stats(v8::HeapStatistics &post_stats)
{
  this->post_stats_ = disa::HeapStats(post_stats);
}

disa::HeapStats disa::GCStats::diff_stats()
{
  return this->diff_stats_;
}

void disa::GCStats::set_diff_stats(v8::HeapStatistics &diff_stats)
{
  this->diff_stats_ = disa::HeapStats(diff_stats);
}

void disa::GCStats::set_diff_stats(disa::HeapStats &diff_stats)
{
  this->diff_stats_ = diff_stats;
}

uint64_t disa::GCStats::started_at()
{
  return this->started_at_;
}

void disa::GCStats::set_started_at(uint64_t time)
{
  this->started_at_ = time;
}

uint64_t disa::GCStats::ended_at()
{
  return this->ended_at_;
}

void disa::GCStats::set_ended_at(uint64_t time)
{
  this->ended_at_ = time;
}

int disa::GCStats::gctype()
{
  return this->gctype_;
}

void disa::GCStats::set_gctype(int type)
{
  this->gctype_ = type;
}
