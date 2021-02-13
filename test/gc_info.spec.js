const gcInfo = require('../lib/index.js')
const semver = require('semver')
const test = require('ava')

const statsKeys = [
  'startedAt',
  'endedAt',
  'duration',
  'gctype',
  'pre',
  'post',
  'diff'
]

const heapKeys = [
  'totalHeapSize',
  'totalHeapSizeExecutable',
  'usedHeapSize',
  'heapSizeLimit',
  'totalPhysicalSize',
  'totalAvailableSize',
  'mallocedMemory',
  'peakMallocedMemory',
  'numberOfNativeContexts',
  'numberOfDetachedContexts'
]

if (semver.gte(semver.clean(process.version), '12.0.0')) {
  heapKeys.push('externalMemory')
}

if (semver.gte(semver.clean(process.version), '14.0.0')) {
  heapKeys.push('totalGlobalHandlesSize')
  heapKeys.push('usedGlobalHandlesSize')
}

test("Should receive stats via event 'data'", async t => {
  const stats = await new Promise(resolve => {
    gcInfo.on('data', resolve)
    global.gc()
  })

  t.deepEqual(statsKeys, Object.keys(stats))
  t.deepEqual(heapKeys, Object.keys(stats.pre))
  t.deepEqual(heapKeys, Object.keys(stats.post))
  t.deepEqual(heapKeys, Object.keys(stats.diff))
})
