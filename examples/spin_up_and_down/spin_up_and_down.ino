// Arduino RBD Motor Library v1.0.3 Example - Spin a motor up and down with events.
// https://github.com/alextaujenis/RBD_Motor
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h> // https://github.com/alextaujenis/RBD_Motor

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