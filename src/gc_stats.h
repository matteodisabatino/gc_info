#ifndef GC_INFO_GC_STATS_H_
#define GC_INFO_GC_STATS_H_

#include <nan.h>

#include "heap_stats.h"

namespace disa
{
  class GCStats
  {
  public:
    GCStats();
    ~GCStats();

    v8::Local<v8::Object> ToV8Object();

    disa::HeapStats pre_stats();
    void set_pre_stats(v8::HeapStatistics &pre_stats);

    disa::HeapStats post_stats();
    void set_post_stats(v8::HeapStatistics &pre_stats);

    disa::HeapStats diff_stats();
    void set_diff_stats(v8::HeapStatistics &diff_stats);
    void set_diff_stats(disa::HeapStats &diff_stats);

    uint64_t started_at();
    void set_started_at(uint64_t time);

    uint64_t ended_at();
    void set_ended_at(uint64_t time);

    int gctype();
    void set_gctype(int type);

  private:
    disa::HeapStats pre_stats_;
    disa::HeapStats post_stats_;
    disa::HeapStats diff_stats_;
    uint64_t started_at_;
    uint64_t ended_at_;
    int gctype_;
  };
} // namespace disa

#endif // GC_INFO_GC_STATS_H_
