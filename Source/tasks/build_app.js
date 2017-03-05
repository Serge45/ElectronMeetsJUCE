'use strict';

var join = require('path').join;
var gulp = require('gulp');
var batch = require('gulp-batch');
var watch = require('gulp-watch');
var utils = require('./utils');

// TODO: bundle js via systemjs
gulp.task('bundle', function() {
  return gulp
    .src(join(__dirname, '../app/*.js'))
    .pipe(gulp.dest('dist'));
});

gulp.task('index', function() {
  return gulp
    .src(join(__dirname, '../app/index.html'))
    .pipe(gulp.dest('dist'));
});

gulp.task('watch', function() {
  var beepOnError = function(done) {
    return function(err) {
      if (err) {
        utils.beepSound();
      }
      done(err);
    };
  };

  watch('app/**/*.js', batch(function(events, done) {
    gulp.start('bundle', beepOnError(done));
  }));
});

gulp.task('build', ['bundle', 'index']);
