// Arduino RBD Motor Library - A simple, non-blocking, real-time library for controlling motors
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
      bool isFullOn();
      int getPwm();
      int getPwmPercent();
      void setPwm(int value);
      void setPwmPercent(int value);
      void rampUp(unsigned long timeout);
      void rampDown(unsigned long timeout);
      void ramp(int value, unsigned long timeout);
      void rampPercent(int value, unsigned long timeout);

    private:
      int _pin;
      int _speed;
      int _start_speed;
      int _target_speed;
      bool _on;
      bool _timed_on;
      bool _ramping;
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