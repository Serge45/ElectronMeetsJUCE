var audioPlugin = (function() {

  var juce = require('./build/Release/juce');

  function playTestSound() {
      juce.playTestSound();
  }

  function queryAllAudioDevices() {
    let devices = juce.getAllAudioDevices();

    let combobox = document.getElementById('output-audio-device-combobox');

    while (combobox.options.length > 1) {
      combobox.remove(1);
    }

    devices.forEach(function(name, idx, arr) {
      let opt = document.createElement('option');
      opt.text = name;
      opt.value = name;
      combobox.add(opt);
    });
  }

  function juceString() {
    var jString = juce.printJUCEString();
    document.getElementById('juce-string').innerText = jString;
  }

  var audioDeviceMessage = require('./protobuf/generatedfiles/audiodevicemanager_pb.js');

  function selectAudioDevice(options) {
    msg = new audioDeviceMessage.DeviceName();
    msg.setName(options.value);
    var err = juce.setAudioDevice(msg.serializeBinary());
    console.log(err);
  }

  function getInputVolume() {
    return juce.getInputVolume();
  }

  setInterval(function() {
    var canvas = document.getElementById("input-volume-canvas");
    var ctx = canvas.getContext("2d");
    ctx.moveTo(0, 0);
    ctx.fillStyle = "#00FF00";
    var fillWidth = getInputVolume() * canvas.width;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillRect(0, 0, fillWidth, canvas.height);
  }, 300);

  return {
    playTestSound: playTestSound,
    queryAllAudioDevices: queryAllAudioDevices,
    juceString: juceString,
    selectAudioDevice: selectAudioDevice,
    getInputVolume: getInputVolume
  }
})();