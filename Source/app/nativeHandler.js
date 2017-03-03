
const juce = require('./native/juce.node');

juce.NativeEmitter.prototype.__proto__ = EventEmitter.prototype;

const emitter = new juce.NativeEmitter();

emitter.on('foo', function () {
  console.log('foo');
});
