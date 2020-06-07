// Arduino RBD Motor Library v2.1.2 Example - Spin a motor up and down with events.
// https://github.com/alextaujenis/RBD_Motor
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h> // https://github.com/alextaujenis/RBD_Motor

RBD::Motor motor(3); // pwm pin

void setup() {
  motor.rampUp(3000);
}

void loop() {
  motor.update();

  if(motor.onTargetSpeed()) {
    if(motor.isOn()) {
      motor.rampDown(3000);
    }
    else {
      motor.rampUp(3000);
    }
  }
}