// Arduino RBD Motor Library v1.1.1 - Control many motors.
// https://github.com/alextaujenis/RBD_Motor
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h> // https://github.com/alextaujenis/RBD_Motor

namespace RBD {
  Motor::Motor(int pwm_pin)
  : _timer() {
    _pwm_pin       = pwm_pin;
    _bidirectional = false;
    pinMode(_pwm_pin, OUTPUT);
  }

  Motor::Motor(int pwm_pin, int forward_pin, int reverse_pin) {
    _pwm_pin        = pwm_pin;
    _forward_pin    = forward_pin;
    _reverse_pin    = reverse_pin;
    _bidirectional  = true;
    pinMode(_pwm_pin, OUTPUT);
    pinMode(_forward_pin, OUTPUT);
    pinMode(_reverse_pin, OUTPUT);
    forward();
  }

  void Motor::on(bool stop_everything) { // default: true
    if(stop_everything) {
      _stopEverything();
    }
    setPwm(255);
  }

  void Motor::off(bool stop_everything) { // default: true
    if(stop_everything) {
      _stopEverything();
    }
    setPwm(0);
  }

  void Motor::forward() {
    if(_bidirectional) {
      _is_forward = true;
      off();
      digitalWrite(_reverse_pin, LOW);
      digitalWrite(_forward_pin, HIGH);
    }
  }

  void Motor::reverse() {
    if(_bidirectional) {
      _is_forward = false;
      off();
      digitalWrite(_forward_pin, LOW);
      digitalWrite(_reverse_pin, HIGH);
    }
  }

  bool Motor::isForward() {
    return _is_forward;
  }

  bool Motor::isReverse() {
    return !_is_forward;
  }

  bool Motor::onForward() {
    if(_bidirectional) {
      if(isForward()) {
        if(!_has_been_forward) {
          _has_been_forward = true;
          return true;
        }
        else {
          return false;
        }
      }
      else {
        _has_been_forward = false;
        return false;
      }
    }
    else {
      return false;
    }
  }

  bool Motor::onReverse() {
    if(_bidirectional) {
      if(isReverse()) {
        if(!_has_been_reverse) {
          _has_been_reverse = true;
          return true;
        }
        else {
          return false;
        }
      }
      else {
        _has_been_reverse = false;
        return false;
      }
    }
    else {
      return false;
    }
  }

  void Motor::toggleDirection() {
    if(_bidirectional) {
      _is_forward = !_is_forward;

      if(isForward()) {
        forward();
      }
      else {
        reverse();
      }
    }
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
    _timer.setTimeout(timeout);
    _timer.restart();
  }

  void Motor::_timedOn() {
    if(_timer.isActive()) {
      on(false); // don't stop everything when turning on
    }
    else {
      off();
      _stopTimedOn();
    }
  }

  bool Motor::isOn() {
    return getPwm() == 255;
  }

  bool Motor::isOff() {
    return getPwm() == 0;
  }

  int Motor::getPwm() {
    return _speed;
  }

  int Motor::getPwmPercent() {
    return int((getPwm() / 255.0 * 100) + 0.5); // add 0.5 for correct rounding
  }

  bool Motor::isPwm(int value) {
    return getPwm() == value;
  }

  bool Motor::isPwmPercent(int value) {
    return getPwmPercent() == value;
  }

  void Motor::setPwm(int value) {
    if(value > -1 && value < 256) {
      analogWrite(_pwm_pin, value);
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
      _timer.setTimeout(timeout);
      _timer.restart();
      _startRamping();
    }
    else {
      _stopRamping();
    }
  }

  void Motor::rampPercent(int value, unsigned long timeout) {
    ramp(int(value / 100.0 * 255), timeout);
  }

  bool Motor::onTargetSpeed() {
    if(_timer.isExpired() && !_timed_on && !_ramping) {
      if(!_hit_target_speed) {
        _hit_target_speed = true;
        return true;
      }
      return false;
    }
    else {
      _hit_target_speed = false;
      return false;
    }
  }


  // private

  void Motor::_ramp() {
    if(_timer.isActive()) {
      setPwm(int(_start_speed + (_timer.getPercentValue() / 100.0 * _speedDifference())));
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