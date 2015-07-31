#include <Arduino.h>
#include <Motor.h>
#include <Timer.h>

Timer timer;

Motor::Motor(int pin) {
  _pin = pin;
}

void Motor::on() {
  setPwm(255);
}

void Motor::off() {
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

void Motor::timedOn(int timeout) {
  _timed_on = true;
  timer.setTimeout(timeout);
  timer.restart();
}

void Motor::_timedOn() {
  if(timer.isActive()) {
    if(isOff()){
      on();
    }
  }
  else {
    off();
    _timed_on = false;
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

void Motor::rampUp(int timeout) {
  ramp(255, timeout);
}

void Motor::rampDown(int timeout) {
  ramp(0, timeout);
}

void Motor::ramp(int value, int timeout) {
  _start_speed  = getPwm();
  _target_speed = value;

  if(_speedShouldChange()) {
    _ramping = true;
    timer.setTimeout(timeout);
    timer.restart();
  }
  else {
    _ramping = false;
  }
}

void Motor::_ramp() {
  if(timer.isActive()) {
    setPwm(int(_start_speed + (timer.getPercentValue() * _speedDifference())));
  }
  else {
    setPwm(_target_speed);
    _ramping = false;
  }
}

bool Motor::_speedShouldChange() {
  return _speedDifference() != 0;
}

int Motor::_speedDifference() {
  return _target_speed - _start_speed;
}

void Motor::rampPercent(int value, int timeout) {
  ramp(int(value / 100.0 * 255), timeout);
}