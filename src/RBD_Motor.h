// Arduino RBD Motor Library v2.0.1 - Control many motors.
// https://github.com/alextaujenis/RBD_Motor
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef RBD_MOTOR_H
#define RBD_MOTOR_H

#include <Arduino.h>
#include <RBD_Timer.h>

namespace RBD {
  class Motor {
    public:
      Motor(int pwm_pin);
      Motor(int pwm_pin, int forward_pin, int reverse_pin);
      void on(bool stop_everything = true);
      void off(bool stop_everything = true);
      void forward();
      void reverse();
      void toggleDirection();
      void update();
      void timedOn(unsigned long timeout);
      bool isOn();
      bool isOff();
      bool isForward();
      bool isReverse();
      int getSpeed();
      int getSpeedPercent();
      void setSpeed(int value);
      void setSpeedPercent(int value);
      void rampUp(unsigned long timeout);
      void rampDown(unsigned long timeout);
      void ramp(int value, unsigned long timeout);
      void rampPercent(int value, unsigned long timeout);
      bool onForward();
      bool onReverse();
      bool onTargetSpeed();
    private:
      int _pwm_pin;
      int _forward_pin;
      int _reverse_pin;
      bool _bidirectional = false;
      bool _is_forward = false;
      bool _has_been_forward = false;
      bool _has_been_reverse = false;
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
      Timer _timer;
  };
}
#endif