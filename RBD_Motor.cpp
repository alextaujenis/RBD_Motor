// Arduino RBD Motor Library - A simple, non-blocking, real-time library for controlling motors
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Motor.h>
#include <RBD_Timer.h>

namespace RBD {

  Timer timer;

  Motor::Motor(int pin) {
    _pin = pin;
  }

  void Motor::on(bool stop_everything) {
    if(stop_everything) {
      _stopEverything();
    }
    setPwm(255);
  }

  void Motor::off(bool stop_everything) {
    if(stop_everything) {
      _stopEverything();
    }
    setPwm(0);
  }

  void Motor::update() {
    if(_timed_on) {
      _timedOn();
    }
    if(_ramping) {
      _ramp();
    }
  }

  void Motor::timedOn(unsigned long timeout) {
    _stopEverything();
    _startTimedOn();
    timer.setTimeout(timeout);
    timer.restart();
  }

  void Motor::_timedOn() {
    if(timer.isActive()) {
      on(false); // don't stop everything when turning on
    }
    else {
      off();
      _stopTimedOn();
    }
  }

  bool Motor::isOn() {
    return _on;
  }

  bool Motor::isOff() {
    return !_on;
  }

  int Motor::getPwm() {
    return _speed;
  }

  int Motor::getPwmPercent() {
    return int(getPwm() / 255.0 * 100);
  }

  void Motor::setPwm(int value) {
    if(value > -1 && value < 256) {
      analogWrite(_pin, value);
      _on = bool(value);
      _speed = value;
    }
  }

  void Motor::setPwmPercent(int value) {
    setPwm(int(value / 100.0 * 255));
  }

  void Motor::rampUp(unsigned long timeout) {
    ramp(255, timeout);
  }

  void Motor::rampDown(unsigned long timeout) {
    ramp(0, timeout);
  }

  void Motor::ramp(int value, unsigned long timeout) {
    _stopEverything();
    _start_speed  = getPwm();
    _target_speed = value;

    if(_speedShouldChange()) {
      _startRamping();
      timer.setTimeout(timeout);
      timer.restart();
    }
    else {
      _stopRamping();
    }
  }

  void Motor::_ramp() {
    if(timer.isActive()) {
      setPwm(int(_start_speed + (timer.getPercentValue() * _speedDifference())));
    }
    else {
      setPwm(_target_speed);
      _stopRamping();
    }
  }

  bool Motor::_speedShouldChange() {
    return _speedDifference() != 0;
  }

  int Motor::_speedDifference() {
    return _target_speed - _start_speed;
  }

  void Motor::rampPercent(int value, unsigned long timeout) {
    ramp(int(value / 100.0 * 255), timeout);
  }

  void Motor::_stopRamping() {
    _ramping = false;
  }

  void Motor::_startRamping() {
    _ramping = true;
  }

  void Motor::_stopTimedOn() {
    _timed_on = false;
  }

  void Motor::_startTimedOn() {
    _timed_on = true;
  }

  void Motor::_stopEverything() {
    _timed_on = false;
    _ramping  = false;
  }
}