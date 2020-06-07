// Arduino RBD Motor Library v2.1.2 Example - Spin a motor forward and reverse with events.
// https://github.com/alextaujenis/RBD_Motor
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h> // https://github.com/alextaujenis/RBD_Motor

// motor shield
RBD::Motor motor(9, 11, 8); // pwm pin, forward pin, reverse pin

void setup() {
  motor.rampUp(5000);
}

void loop() {
  motor.update();

  if(motor.onTargetSpeed()) {
    if(motor.isOn()) {
      motor.rampDown(3000);
    }
    else {
      motor.toggleDirection();
      motor.rampUp(5000);
    }
  }
}