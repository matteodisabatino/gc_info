export interface GcStats {
  /**
   * Number of bytes V8 has allocated for the heap.
   */
  totalHeapSize: number

  /**
   * Number of bytes for compiled bytecode and JITed code.
   */
  totalHeapSizeExecutable: number

  /**
   * Number of bytes in use by application data.
   */
  usedHeapSize: number

  /**
   * The absolute limit the heap cannot exceed.
   */
  heapSizeLimit: number

  /**
   * Committed size. (Node.js 0.12+)
   */
  totalPhysicalSize?: number

  /**
   * Available heap size. (Node.js 4+)
   */
  totalAvailableSize?: number

  /**
   * Current amount of memory, obtained via malloc. (Node.js 7+)
   */
  mallocedMemory?: number

  /**
   * Peak amount of memory, obtained via malloc. (Node.js 7+)
   */
  peakMallocedMemory?: number

  /**
   * Number of the top-level contexts currently active. (Node.js 10+)
   */
  numberOfNativeContexts?: number

  /**
   * Number of contexts that were detached and not yet garbage collected. (Node.js 10+)
   */
  numberOfDetachedContexts?: number

  /**
   * Number of bytes of memory allocated outside of v8's heap. (Node.js 11+)
   */
  externalMemory?: number

  /**
   * Size of all global handles in the heap. (Node.js 14+)
   */
  totalGlobalHandlesSize?: number

  /**
   * Size of all allocated/used global handles in the heap. (Node.js 14+)
   */
  usedGlobalHandlesSize?: number
}

export interface GcInfo {
  /**
   * The moment the GC started (Unix timestamp in milliseconds).
   */
  startedAt: number

  /**
   * The moment the GC ended (Unix timestamp in milliseconds).
   */
  endedAt: number

  /**
   * The time the GC has been active (difference between endedAt and
   * startedAt).
   */
  duration: number

  /**
   * Memory allocation type.
   */
  gctype: number

  /**
   * Stats at the moment the GC started
   */
  pre: GcStats

  /**
   * Stats at the moment the GC ended
   */
  post: GcStats

  /**
   * Effective stats (difference between post and pre).
   */
  diff: GcStats
}

export function on(event: 'data', callback: (stats: GcInfo) => void): void
export function off(event: 'data', callback?: (stats: GcInfo) => void): void
export const path: string
export enum GcType {
  Scavenge = 1,
  'Mark/Sweep/Compact' = 2,
  IncrementalMarking = 4,
  'Weak/PhantomCallbackProcessing' = 8,
  All = 15
}

export const version: string
