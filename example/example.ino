// Arduino RBD Motor Example - Spin a motor up and then down.
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h>
#include <RBD_Motor.h>

RBD::Motor motor(3); // PWM pin 3

void setup() {
  motor.rampUp(1000);
}

void loop() {
  motor.update();

  if(motor.onTargetSpeed()) {
    if(motor.isOn()) {
      motor.rampDown(1000);
    }
    if(motor.isOff()) {
      motor.rampUp(1000);
    }
  }
}