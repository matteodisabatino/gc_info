#include "heap_stats.h"

#include <nan.h>

disa::HeapStats disa::operator-(disa::HeapStats &lhs, disa::HeapStats &rhs)
{
    disa::HeapStats result;
    result.set_total_heap_size(lhs.total_heap_size() - rhs.total_heap_size());
    result.set_total_heap_size_executable(lhs.total_heap_size_executable() - rhs.total_heap_size_executable());
    result.set_used_heap_size(lhs.used_heap_size() - rhs.used_heap_size());
    result.set_heap_size_limit(lhs.heap_size_limit() - rhs.heap_size_limit());

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
    result.set_total_physical_size(lhs.total_physical_size() - rhs.total_physical_size());
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
    result.set_total_available_size(lhs.total_available_size() - rhs.total_available_size());
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
    result.set_malloced_memory(lhs.malloced_memory() - rhs.malloced_memory());
    result.set_peak_malloced_memory(lhs.peak_malloced_memory() - rhs.peak_malloced_memory());
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
    result.set_number_of_native_contexts(lhs.number_of_native_contexts() - rhs.number_of_native_contexts());
    result.set_number_of_detached_contexts(lhs.number_of_detached_contexts() - rhs.number_of_detached_contexts());
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
    result.set_external_memory(lhs.external_memory() - rhs.external_memory());
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
    result.set_total_global_handles_size(lhs.total_global_handles_size() - rhs.total_global_handles_size());
    result.set_used_global_handles_size(lhs.used_global_handles_size() - rhs.used_global_handles_size());
#endif

    return result;
}

disa::HeapStats::HeapStats() {}

disa::HeapStats::HeapStats(v8::HeapStatistics &stats)
{
    this->total_heap_size_ = static_cast<double>(stats.total_heap_size());
    this->total_heap_size_executable_ = static_cast<double>(stats.total_heap_size_executable());
    this->used_heap_size_ = static_cast<double>(stats.used_heap_size());
    this->heap_size_limit_ = static_cast<double>(stats.heap_size_limit());

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
    this->total_physical_size_ = static_cast<double>(stats.total_physical_size());
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
    this->total_available_size_ = static_cast<double>(stats.total_available_size());
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
    this->malloced_memory_ = static_cast<double>(stats.malloced_memory());
    this->peak_malloced_memory_ = static_cast<double>(stats.peak_malloced_memory());
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
    this->number_of_native_contexts_ = static_cast<double>(stats.number_of_native_contexts());
    this->number_of_detached_contexts_ = static_cast<double>(stats.number_of_detached_contexts());
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
    this->external_memory_ = static_cast<double>(stats.external_memory());
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
    this->total_global_handles_size_ = static_cast<double>(stats.total_global_handles_size());
    this->used_global_handles_size_ = static_cast<double>(stats.used_global_handles_size());
#endif
}

disa::HeapStats::~HeapStats() {}

v8::Local<v8::Object> disa::HeapStats::ToV8Object()
{
    v8::Local<v8::Object> obj = Nan::New<v8::Object>();
    Nan::Set(obj, Nan::New("totalHeapSize").ToLocalChecked(), Nan::New<v8::Number>(this->total_heap_size_));
    Nan::Set(obj, Nan::New("totalHeapSizeExecutable").ToLocalChecked(), Nan::New<v8::Number>(this->total_heap_size_executable_));
    Nan::Set(obj, Nan::New("usedHeapSize").ToLocalChecked(), Nan::New<v8::Number>(this->used_heap_size_));
    Nan::Set(obj, Nan::New("heapSizeLimit").ToLocalChecked(), Nan::New<v8::Number>(this->heap_size_limit_));

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
    Nan::Set(obj, Nan::New("totalPhysicalSize").ToLocalChecked(), Nan::New<v8::Number>(this->total_physical_size_));
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
    Nan::Set(obj, Nan::New("totalAvailableSize").ToLocalChecked(), Nan::New<v8::Number>(this->total_available_size_));
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
    Nan::Set(obj, Nan::New("mallocedMemory").ToLocalChecked(), Nan::New<v8::Number>(this->malloced_memory_));
    Nan::Set(obj, Nan::New("peakMallocedMemory").ToLocalChecked(), Nan::New<v8::Number>(this->peak_malloced_memory_));
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
    Nan::Set(obj, Nan::New("numberOfNativeContexts").ToLocalChecked(), Nan::New<v8::Number>(this->number_of_native_contexts_));
    Nan::Set(obj, Nan::New("numberOfDetachedContexts").ToLocalChecked(), Nan::New<v8::Number>(this->number_of_detached_contexts_));
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
    Nan::Set(obj, Nan::New("externalMemory").ToLocalChecked(), Nan::New<v8::Number>(this->external_memory_));
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
    Nan::Set(obj, Nan::New("totalGlobalHandlesSize").ToLocalChecked(), Nan::New<v8::Number>(this->total_global_handles_size_));
    Nan::Set(obj, Nan::New("usedGlobalHandlesSize").ToLocalChecked(), Nan::New<v8::Number>(this->used_global_handles_size_));
#endif

    return obj;
}

double disa::HeapStats::total_heap_size()
{
    return this->total_heap_size_;
}

void disa::HeapStats::set_total_heap_size(double total_heap_size)
{
    this->total_heap_size_ = total_heap_size;
}

void disa::HeapStats::set_total_heap_size(size_t total_heap_size)
{
    this->total_heap_size_ = static_cast<double>(total_heap_size);
}

double disa::HeapStats::total_heap_size_executable()
{
    return this->total_heap_size_executable_;
}

void disa::HeapStats::set_total_heap_size_executable(double total_heap_size_executable)
{
    this->total_heap_size_executable_ = total_heap_size_executable;
}

void disa::HeapStats::set_total_heap_size_executable(size_t total_heap_size_executable)
{
    this->total_heap_size_executable_ = static_cast<double>(total_heap_size_executable);
}

double disa::HeapStats::used_heap_size()
{
    return this->used_heap_size_;
}

void disa::HeapStats::set_used_heap_size(double used_heap_size)
{
    this->used_heap_size_ = used_heap_size;
}

void disa::HeapStats::set_used_heap_size(size_t used_heap_size)
{
    this->used_heap_size_ = static_cast<double>(used_heap_size);
}

double disa::HeapStats::heap_size_limit()
{
    return this->heap_size_limit_;
}

void disa::HeapStats::set_heap_size_limit(double heap_size_limit)
{
    this->heap_size_limit_ = heap_size_limit;
}

void disa::HeapStats::set_heap_size_limit(size_t heap_size_limit)
{
    this->heap_size_limit_ = static_cast<double>(heap_size_limit);
}

#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
double disa::HeapStats::total_physical_size()
{
    return this->total_physical_size_;
}

void disa::HeapStats::set_total_physical_size(double total_physical_size)
{
    this->total_physical_size_ = total_physical_size;
}

void disa::HeapStats::set_total_physical_size(size_t total_physical_size)
{
    this->total_physical_size_ = static_cast<double>(total_physical_size);
}
#endif

#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
double disa::HeapStats::total_available_size()
{
    return this->total_available_size_;
}

void disa::HeapStats::set_total_available_size(double total_available_size)
{
    this->total_available_size_ = total_available_size;
}

void disa::HeapStats::set_total_available_size(size_t total_available_size)
{
    this->total_available_size_ = static_cast<double>(total_available_size);
}
#endif

#if NODE_MODULE_VERSION >= NODE_7_0_MODULE_VERSION
double disa::HeapStats::malloced_memory()
{
    return this->malloced_memory_;
}

void disa::HeapStats::set_malloced_memory(double malloced_memory)
{
    this->malloced_memory_ = malloced_memory;
}

void disa::HeapStats::set_malloced_memory(size_t malloced_memory)
{
    this->malloced_memory_ = static_cast<double>(malloced_memory);
}

double disa::HeapStats::peak_malloced_memory()
{
    return this->peak_malloced_memory_;
}

void disa::HeapStats::set_peak_malloced_memory(double peak_malloced_memory)
{
    this->peak_malloced_memory_ = peak_malloced_memory;
}

void disa::HeapStats::set_peak_malloced_memory(size_t peak_malloced_memory)
{
    this->peak_malloced_memory_ = static_cast<double>(peak_malloced_memory);
}
#endif

#if NODE_MODULE_VERSION >= NODE_10_0_MODULE_VERSION
double disa::HeapStats::number_of_native_contexts()
{
    return this->number_of_native_contexts_;
}

void disa::HeapStats::set_number_of_native_contexts(double number_of_native_contexts)
{
    this->number_of_native_contexts_ = number_of_native_contexts;
}

void disa::HeapStats::set_number_of_native_contexts(size_t number_of_native_contexts)
{
    this->number_of_native_contexts_ = static_cast<double>(number_of_native_contexts);
}

double disa::HeapStats::number_of_detached_contexts()
{
    return this->number_of_detached_contexts_;
}

void disa::HeapStats::set_number_of_detached_contexts(double number_of_detached_contexts)
{
    this->number_of_detached_contexts_ = number_of_detached_contexts;
}

void disa::HeapStats::set_number_of_detached_contexts(size_t number_of_detached_contexts)
{
    this->number_of_detached_contexts_ = static_cast<double>(number_of_detached_contexts);
}
#endif

#if NODE_MODULE_VERSION >= NODE_11_0_MODULE_VERSION
double disa::HeapStats::external_memory()
{
    return this->external_memory_;
}

void disa::HeapStats::set_external_memory(double external_memory)
{
    this->external_memory_ = external_memory;
}

void disa::HeapStats::set_external_memory(size_t external_memory)
{
    this->external_memory_ = static_cast<double>(external_memory);
}
#endif

#if NODE_MODULE_VERSION >= NODE_14_0_MODULE_VERSION
double disa::HeapStats::total_global_handles_size()
{
    return this->total_global_handles_size_;
}

void disa::HeapStats::set_total_global_handles_size(double total_global_handles_size)
{
    this->total_global_handles_size_ = total_global_handles_size;
}

void disa::HeapStats::set_total_global_handles_size(size_t total_global_handles_size)
{
    this->total_global_handles_size_ = static_cast<double>(total_global_handles_size);
}

double disa::HeapStats::used_global_handles_size()
{
    return this->used_global_handles_size_;
}

void disa::HeapStats::set_used_global_handles_size(double used_global_handles_size)
{
    this->used_global_handles_size_ = used_global_handles_size;
}

void disa::HeapStats::set_used_global_handles_size(size_t used_global_handles_size)
{
    this->used_global_handles_size_ = static_cast<double>(used_global_handles_size);
}
#endif
