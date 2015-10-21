// Arduino RBD Motor Library v1.0.4 - Control many motors.
// https://github.com/alextaujenis/RBD_Motor
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef RBD_MOTOR_H
#define RBD_MOTOR_H

#include <Arduino.h>

namespace RBD {
  class Motor {
    public:
      Motor(int pin);
      void on(bool stop_everything = true);
      void off(bool stop_everything = true);
      void update();
      void timedOn(unsigned long timeout);
      bool isOn();
      bool isOff();
      int getPwm();
      int getPwmPercent();
      bool isPwm(int value);
      bool isPwmPercent(int value);
      void setPwm(int value);
      void setPwmPercent(int value);
      void rampUp(unsigned long timeout);
      void rampDown(unsigned long timeout);
      void ramp(int value, unsigned long timeout);
      void rampPercent(int value, unsigned long timeout);
      bool onTargetSpeed();
    private:
      int _pin;
      int _speed;
      int _start_speed;
      int _target_speed;
      bool _timed_on;
      bool _ramping;
      bool _hit_target_speed = false;
      void _timedOn();
      void _ramp();
      bool _speedShouldChange();
      int _speedDifference();
      void _stopTimedOn();
      void _startTimedOn();
      void _stopRamping();
      void _startRamping();
      void _stopEverything();
  };
}
#endif