// Arduino RBD Motor Library v2.1.2 - Control many motors.
// https://github.com/alextaujenis/RBD_Motor
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <Arduino.h>
#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h> // https://github.com/alextaujenis/RBD_Motor

namespace RBD {
  // constructor
  Motor::Motor(int pwm_pin)
  : _timer() {
    _pwm_pin       = pwm_pin;
    _bidirectional = false;
    pinMode(_pwm_pin, OUTPUT);
  }

  // overloaded constructor for bidirectional control
  Motor::Motor(int pwm_pin, int forward_pin, int reverse_pin)
  : _timer() {
    _pwm_pin        = pwm_pin;
    _forward_pin    = forward_pin;
    _reverse_pin    = reverse_pin;
    _bidirectional  = true;
    pinMode(_pwm_pin, OUTPUT);
    pinMode(_forward_pin, OUTPUT);
    pinMode(_reverse_pin, OUTPUT);
    forward();
  }

  void Motor::on(bool _stop_everything) { // default: true
    setSpeed(255, _stop_everything);
  }

  void Motor::off(bool _stop_everything) { // default: true
    setSpeed(0, _stop_everything);
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
          return _has_been_forward = true;
        }
        // else
        return false;
      }
      // else
      return _has_been_forward = false;
    }
    // else
    return false;
  }

  bool Motor::onReverse() {
    if(_bidirectional) {
      if(isReverse()) {
        if(!_has_been_reverse) {
          return _has_been_reverse = true;
        }
        // else
        return false;
      }
      // else
      return _has_been_reverse = false;
    }
    // else
    return false;
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

  bool Motor::isOn() {
    return getSpeed() == 255;
  }

  bool Motor::isOff() {
    return getSpeed() == 0;
  }

  int Motor::getSpeed() {
    return _speed;
  }

  int Motor::getSpeedPercent() {
    return int((getSpeed() / 255.0 * 100) + 0.5); // add 0.5 for correct rounding
  }

  void Motor::setSpeed(int value, bool _stop_everything) { // default: true
    if(value > -1 && value < 256) {
      if(_stop_everything) {
        _stopEverything();
      }
      else {
        _stop_events = false;
      }

      if(_speed != value) {
        _speed = value;
        analogWrite(_pwm_pin, _speed);
      }
    }
  }

  void Motor::setSpeedPercent(int value, bool _stop_everything) { // default: true
    setSpeed(int(value / 100.0 * 255), _stop_everything);
  }

  void Motor::rampUp(unsigned long timeout) {
    ramp(255, timeout);
  }

  void Motor::rampDown(unsigned long timeout) {
    ramp(0, timeout);
  }

  void Motor::ramp(int value, unsigned long timeout) {
    _stopEverything();
    _start_speed  = getSpeed();
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
    if(_timer.isExpired() && !_timed_on && !_ramping && !_stop_events) {
      if(!_hit_target_speed) {
        return _hit_target_speed = true;
      }
      // else
      return false;
    }
    // else
    return _hit_target_speed = false;
  }


  // private

  void Motor::_timedOn() {
    if(_timer.isActive()) {
      on(false); // don't stop everything when turning on
    }
    else {
      off();
      _stopTimedOn();
    }
  }

  void Motor::_ramp() {
    if(_timer.isActive()) {
      setSpeed(int(_start_speed + (_timer.getPercentValue() / 100.0 * _speedDifference())), false); // don't stop everything
    }
    else {
      setSpeed(_target_speed, false); // don't stop everything
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
    _timed_on    = false;
    _ramping     = false;
    _stop_events = true;
  }
}