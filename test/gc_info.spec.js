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
  'heapSizeLimit'
]

if (semver.gte(semver.clean(process.version), '0.12.0')) {
  heapKeys.push('totalPhysicalSize')
}

if (semver.gte(semver.clean(process.version), '4.0.0')) {
  heapKeys.push('totalAvailableSize')
}

if (semver.gte(semver.clean(process.version), '7.0.0')) {
  heapKeys.push('mallocedMemory')
  heapKeys.push('peakMallocedMemory')
}

if (semver.gte(semver.clean(process.version), '10.0.0')) {
  heapKeys.push('numberOfNativeContexts')
  heapKeys.push('numberOfDetachedContexts')
}

if (semver.gte(semver.clean(process.version), '11.0.0')) {
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
