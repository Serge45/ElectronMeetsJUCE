'use strict';

var argv = require('minimist')(process.argv);

exports.beepSound = function() {
  process.stdout.write('\u0007');
};
