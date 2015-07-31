// Arduino Motor Library - A simple, non-blocking, real-time library for controlling motors
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  public:
    Motor(int pin);
    void on();
    void off();
    void update();
    void timedOn(int timeout);
    bool isOn();
    bool isOff();
    int getPwm();
    int getPwmPercent();
    void setPwm(int value);
    void setPwmPercent(int value);
    void rampUp(int timeout);
    void rampDown(int timeout);
    void ramp(int value, int timeout);
    void rampPercent(int value, int timeout);

  private:
    int _pin;
    int _speed;
    bool _ramping;
    int _start_speed;
    int _target_speed;
    bool _on;
    bool _timed_on;
    void _timedOn();
    void _ramp();
    bool _speedShouldChange();
    int _speedDifference();
};

#endif