#include <Arduino.h>
#include <Motor.h>
#include <Timer.h>

Timer timer;

Motor::Motor(int pin) {
  _pin = pin;
}

void Motor::on() {
  pwm(255);
}

void Motor::off() {
  pwm(0);
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
  timer.reset()
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

int Motor::speed() {
  return _speed;
}

int Motor::speedPercent() {
  return int(speed() / 255);
}

void Motor::pwm(int value) {
  if(value > -1 && value < 256) {
    analogWrite(_pin, value);
    _on = bool(value);
    _speed = value;
  }
}

void Motor::pwmPercent(int value) {
  pwm(int(value / 100 * 255));
}

void Motor::rampUp(int timeout) {
  ramp(255, timeout);
}

void Motor::rampDown(int timeout) {
  ramp(0, timeout);
}

void Motor::ramp(int value, int timeout) {
  _start_speed  = speed();
  _target_speed = value;

  if(_speedShouldChange()) {
    _ramping = true;
    timer.setTimeout(timeout);
    timer.reset();
  }
  else {
    _ramping = false;
  }
}

void Motor::_ramp() {
  if(timer.isActive()) {
    pwm(int(_start_speed + (timer.getPercentValue() * _speedDifference()));
  }
  else {
    pwm(_target_speed);
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
  ramp(int(value / 100 * 255), timeout);
}