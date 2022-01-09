'use strict'
var bindings = require('bindings')

var manifest = require('../package.json')

var gcInfo = bindings('gc_info.node')

module.exports = gcInfo
module.exports.GcType = {
  1: 'Scavenge',
  2: 'Mark/Sweep/Compact',
  4: 'IncrementalMarking',
  8: 'Weak/PhantomCallbackProcessing',
  15: 'All',
  Scavenge: 1,
  'Mark/Sweep/Compact': 2,
  IncrementalMarking: 4,
  'Weak/PhantomCallbackProcessing': 8,
  All: 15
}

module.exports.version = manifest.version
