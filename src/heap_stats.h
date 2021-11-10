#ifndef GC_INFO_HEAP_STATS_H_
#define GC_INFO_HEAP_STATS_H_

#include <nan.h>

namespace disa
{
    class HeapStats
    {
    public:
        friend HeapStats operator-(HeapStats &lhs, HeapStats &rhs);

        HeapStats();
        HeapStats(v8::HeapStatistics &stats);
        ~HeapStats();

        v8::Local<v8::Object> ToV8Object();

        double total_heap_size();
        void set_total_heap_size(double total_heap_size);
        void set_total_heap_size(size_t total_heap_size);

        double total_heap_size_executable();
        void set_total_heap_size_executable(double total_heap_size_executable);
        void set_total_heap_size_executable(size_t total_heap_size_executable);

        double used_heap_size();
        void set_used_heap_size(double used_heap_size);
        void set_used_heap_size(size_t used_heap_size);

        double heap_size_limit();
        void set_heap_size_limit(double heap_size_limit);
        void set_heap_size_limit(size_t heap_size_limit);

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
        double total_physical_size();
        void set_total_physical_size(double total_physical_size);
        void set_total_physical_size(size_t total_physical_size);
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
        double total_available_size();
        void set_total_available_size(double total_available_size);
        void set_total_available_size(size_t total_available_size);
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
        double malloced_memory();
        void set_malloced_memory(double malloced_memory);
        void set_malloced_memory(size_t malloced_memory);

        double peak_malloced_memory();
        void set_peak_malloced_memory(double peak_malloced_memory);
        void set_peak_malloced_memory(size_t peak_malloced_memory);
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
        double number_of_native_contexts();
        void set_number_of_native_contexts(double number_of_native_contexts);
        void set_number_of_native_contexts(size_t number_of_native_contexts);

        double number_of_detached_contexts();
        void set_number_of_detached_contexts(double number_of_detached_contexts);
        void set_number_of_detached_contexts(size_t number_of_detached_contexts);
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
        double external_memory();
        void set_external_memory(double external_memory);
        void set_external_memory(size_t external_memory);
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
        double total_global_handles_size();
        void set_total_global_handles_size(double total_global_handles_size);
        void set_total_global_handles_size(size_t total_global_handles_size);

        double used_global_handles_size();
        void set_used_global_handles_size(double used_global_handles_size);
        void set_used_global_handles_size(size_t used_global_handles_size);
#endif

    private:
        double total_heap_size_;
        double total_heap_size_executable_;
        double used_heap_size_;
        double heap_size_limit_;

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
        double total_physical_size_;
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
        double total_available_size_;
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
        double malloced_memory_;
        double peak_malloced_memory_;
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
        double number_of_native_contexts_;
        double number_of_detached_contexts_;
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
        double external_memory_;
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
        double total_global_handles_size_;
        double used_global_handles_size_;
#endif
    };
} // namespace disa

#endif //GC_INFO_HEAP_STATS_H_
