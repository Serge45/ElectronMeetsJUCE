var audioPlugin = (function() {

  var juce = require('./build/Release/juce');

  function playTestSound() {
      juce.playTestSound();
  }

  function updateCombobox(combobox, items) {

    while (combobox.options.length > 1) {
      combobox.remove(1);
    }

    items.forEach(function(name, idx, arr) {
      let opt = document.createElement('option');
      opt.text = name;
      opt.value = name;
      combobox.add(opt);
    });
  }

  function queryAllAudioDevices() {
    let devices = juce.getAllAudioDevices();
    let combobox = document.getElementById('output-audio-device-combobox');
    updateCombobox(combobox, devices);
  }

  function juceString() {
    var jString = juce.printJUCEString();
    document.getElementById('juce-string').innerText = jString;
  }

  function selectAudioDeviceType(options) {
    juce.setAudioDeviceType(options.value);
  }

  function getAudioDeviceTypes() {
    let types = juce.getAllAudioDeviceTypes()
    let combobox = document.getElementById('audio-device-types');
    updateCombobox(combobox, types);
  }

  function selectAudioDevice(options) {
    var err = juce.setAudioDevice(options.value);
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
  }, 100);

  return {
    playTestSound: playTestSound,
    queryAllAudioDevices: queryAllAudioDevices,
    juceString: juceString,
    selectAudioDevice: selectAudioDevice,
    getInputVolume: getInputVolume,
    getAudioDeviceTypes: getAudioDeviceTypes,
    selectAudioDeviceType: selectAudioDeviceType,
  }
})();