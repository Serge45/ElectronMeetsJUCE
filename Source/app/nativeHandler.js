
const juce = require('./native/juce');

juce.NativeEmitter.prototype.__proto__ = EventEmitter.prototype;

const emitter = new juce.NativeEmitter();

emitter.on('foo', function () {
  console.log('foo');
});
