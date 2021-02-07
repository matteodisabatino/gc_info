#ifndef GC_INFO_GC_STATS_H_
#define GC_INFO_GC_STATS_H_

#include <nan.h>

#include "heap_stats.h"

namespace apio
{
  class GCStats
  {
  public:
    GCStats();
    ~GCStats();

    v8::Local<v8::Object> ToV8Object();

    apio::HeapStats pre_stats();
    void set_pre_stats(v8::HeapStatistics &pre_stats);

    apio::HeapStats post_stats();
    void set_post_stats(v8::HeapStatistics &pre_stats);

    apio::HeapStats diff_stats();
    void set_diff_stats(v8::HeapStatistics &diff_stats);
    void set_diff_stats(apio::HeapStats &diff_stats);

    uint64_t started_at();
    void set_started_at(uint64_t time);

    uint64_t ended_at();
    void set_ended_at(uint64_t time);

    int gctype();
    void set_gctype(int type);

  private:
    apio::HeapStats pre_stats_;
    apio::HeapStats post_stats_;
    apio::HeapStats diff_stats_;
    uint64_t started_at_;
    uint64_t ended_at_;
    int gctype_;
  };
} // namespace apio

#endif // GC_INFO_GC_STATS_H_
