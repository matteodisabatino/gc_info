# gc_info

Gives you information about V8 GC after its execution. Based on [node-gcstats](https://github.com/dainis/node-gcstats).

This module is designed to support only current, active and in maintenance Node.js versions according to [official Node.js Release schedule](https://github.com/nodejs/Release). Both source code and binaries for Linux, macOS and Windows are provided.

It is a C++ addon written using the module [nan](https://github.com/nodejs/nan) and following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) except for the lint. If you find something not compliant with, please provide a pull request.

In general every pull request that will:

- Let the code be compliant to Google C++ Style Guide
- Improve performances
- Save memory
- Add features

are well accepted.

## Usage

Require the module and subscribe the `data` event.

### Basic

```js
const gcInfo = require('@matteodisabatino/gc_info')

gcInfo.on('data', info => {
  console.log('GC information: ', info)
})
```

### Unsubscribe specific listener

```js
const gcInfo = require('@matteodisabatino/gc_info')

const listener1 = info => {
  console.log('listener1 - GC information: ', info)
}

const listener2 = info => {
  console.log('listener2 - GC information: ', info)
}

gcInfo.on('data', listener1)
gcInfo.on('data', listener2)

gcInfo.off('data', listener1) // listener1 is no longer active but you will
                              // still receive data via listener2.
```

### Unsubscribe all listeners

```js
const gcInfo = require('@matteodisabatino/gc_info')

const listener1 = info => {
  console.log('listener1 - GC information: ', info)
}

const listener2 = info => {
  console.log('listener2 - GC information: ', info)
}

gcInfo.on('data', listener1)
gcInfo.on('data', listener2)

gcInfo.off('data') // Both listener1 and listener2 are no longer active. You
                   // will not receive any data until you will subscribe the
                   // `data` event again.
```

## Information

```js
{
  startedAt: Number,
  endedAt: Number,
  duration: Number,
  gctype: Number,
  pre: {
    totalHeapSize: Number,
    totalHeapSizeExecutable: Number,
    usedHeapSize: Number,
    heapSizeLimit: Number,
    totalPhysicalSize: Number,
    totalAvailableSize: Number,
    mallocedMemory: Number,
    peakMallocedMemory: Number,
    numberOfNativeContexts: Number,
    numberOfDetachedContexts: Number,
    externalMemory: Number,
    totalGlobalHandlesSize: Number,
    usedGlobalHandlesSize: Number
  },
  post: {
    totalHeapSize: Number,
    totalHeapSizeExecutable: Number,
    usedHeapSize: Number,
    heapSizeLimit: Number,
    totalPhysicalSize: Number,
    totalAvailableSize: Number,
    mallocedMemory: Number,
    peakMallocedMemory: Number,
    numberOfNativeContexts: Number,
    numberOfDetachedContexts: Number,
    externalMemory: Number,
    totalGlobalHandlesSize: Number,
    usedGlobalHandlesSize: Number
  },
  diff: {
    totalHeapSize: Number,
    totalHeapSizeExecutable: Number,
    usedHeapSize: Number,
    heapSizeLimit: Number,
    totalPhysicalSize: Number,
    totalAvailableSize: Number,
    mallocedMemory: Number,
    peakMallocedMemory: Number,
    numberOfNativeContexts: Number,
    numberOfDetachedContexts: Number,
    externalMemory: Number,
    totalGlobalHandlesSize: Number,
    usedGlobalHandlesSize: Number
  }
}
```

### Property meaning

- startedAt: The moment the GC started (Unix timestamp in milliseconds).
- endedAt: The moment the GC ended (Unix timestamp in milliseconds).
- duration: The time the GC has been active (difference between endedAt and startedAt).
- gctype: Memory allocation type. According to [v8 source code](https://github.com/nodejs/node/blob/a91a95f8203c6683ad497c0cbd4cb5f48030bd23/deps/v8/include/v8.h#L7588-L7595) possible values are:
  - 1: Scavenge
  - 2: Mark/Sweep/Compact
  - 4: Incremental marking
  - 8: Weak/Phantom callback processing
  - 15: All

- totalHeapSize: Number of bytes V8 has allocated for the heap. This can grow if usedHeap needs more.
- totalHeapSizeExecutable: Number of bytes for compiled bytecode and JITed code.
- usedHeapSize: Number of bytes in use by application data.
- heapSizeLimit: The absolute limit the heap cannot exceed.
- totalPhysicalSize: Committed size.
- totalAvailableSize: Available heap size.
- mallocedMemory: Current amount of memory, obtained via malloc.
- peakMallocedMemory: Peak amount of memory, obtained via malloc.
- numberOfNativeContexts: Number of the top-level contexts currently active. Increase of this number over time indicates a memory leak.
- numberOfDetachedContexts: Number of contexts that were detached and not yet garbage collected. This number being non-zero indicates a potential memory leak.
- externalMemory: Number of bytes of memory allocated outside of v8's heap. (Node.js 12+)
- totalGlobalHandlesSize: Size of all global handles in the heap. (Node.js 14+)
- usedGlobalHandlesSize: Size of all allocated/used global handles in the heap. (Node.js 14+)
