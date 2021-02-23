'use strict'
const bindings = require('bindings')

const gcInfo = bindings('gc_info.node')

module.exports = gcInfo
module.exports.GcType = {
  Scavenge: 1,
  'Mark/Sweep/Compact': 2,
  IncrementalMarking: 4,
  'Weak/PhantomCallbackProcessing': 8,
  All: 15
}
