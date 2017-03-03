'use strict';

var gulp = require('gulp');
var requireDir = require('require-dir');

requireDir('./tasks', { recurse: false });

gulp.task('default', ['build']);
