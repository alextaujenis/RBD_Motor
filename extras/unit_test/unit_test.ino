// Arduino RBD Motor Library v2.1.2 - Unit test coverage.
// https://github.com/alextaujenis/RBD_Motor
// Copyright (c) 2015 Alex Taujenis - MIT License

#include <ArduinoUnit.h> // https://github.com/mmurdoch/arduinounit
#include <RBD_Timer.h>   // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Motor.h>   // https://github.com/alextaujenis/RBD_Motor

// Test setup: connect pin 3 to pin 2 with a small jumper wire to test the motor pwm pin,
// also connect a jumper from digital pin 22 to pin 23 to test the motor forward pin,
// and connect a jumper from digital pin 26 to pin 27 to test the motor reverse pin

RBD::Motor motor(3,22,26);

const int pwm_pin = 2;
const int fwd_pin = 23;
const int rev_pin = 27;

// test helpers
unsigned long getPulseTime() { return pulseIn(pwm_pin, HIGH); }
bool isOn()     { return digitalRead(pwm_pin); }
bool isOff()    { return !isOn(); }
bool fwdIsOn()  { return digitalRead(fwd_pin); }
bool fwdIsOff() { return !fwdIsOn(); }
bool revIsOn()  { return digitalRead(rev_pin); }
bool revIsOff() { return !revIsOn(); }

// on
  test(on_should_turn_on_the_motor) {
    motor.on();
    assertTrue(isOn());
    testCleanup();
  }

// off
  test(off_should_turn_off_the_motor) {
    motor.on();
    motor.off();
    assertTrue(isOff());
    testCleanup();
  }

// forward
  test(forward_should_set_the_motor_forward) {
    motor.reverse();
    motor.forward();
    assertTrue(fwdIsOn());
    assertTrue(revIsOff());
    testCleanup();
  }

// reverse
  test(reverse_should_set_the_motor_reverse) {
    motor.forward();
    motor.reverse();
    assertTrue(revIsOn());
    assertTrue(fwdIsOff());
    testCleanup();
  }

// isForward
  test(isForward_should_return_true_when_the_motor_is_forward) {
    motor.forward();
    assertTrue(motor.isForward());
    testCleanup();
  }

  test(isForward_should_return_false_when_the_motor_is_in_reverse) {
    motor.reverse();
    assertFalse(motor.isForward());
    testCleanup();
  }

// isReverse
  test(isReverse_should_return_true_when_the_motor_is_in_reverse) {
    motor.reverse();
    assertTrue(motor.isReverse());
    testCleanup();
  }

  test(isReverse_should_return_false_when_the_motor_is_forward) {
    motor.forward();
    assertFalse(motor.isReverse());
    testCleanup();
  }

// onForward
  test(onForward_should_return_true_when_the_motor_is_set_forward) {
    motor.forward();
    assertTrue(motor.onForward());
    testCleanup();
  }

  test(onForward_should_return_true_only_once_when_the_motor_is_set_forward) {
    motor.forward();
    assertTrue(motor.onForward());
    assertFalse(motor.onForward());
    assertFalse(motor.onForward());
    testCleanup();
  }

  test(onForward_should_return_false_if_the_motor_is_set_in_reverse) {
    motor.reverse();
    assertFalse(motor.onForward());
    assertFalse(motor.onForward());
    testCleanup();
  }

// onReverse
  test(onReverse_should_return_true_when_the_motor_is_set_in_reverse) {
    motor.reverse();
    assertTrue(motor.onReverse());
    testCleanup();
  }

  test(onReverse_should_return_true_only_once_when_the_motor_is_set_in_reverse) {
    motor.reverse();
    assertTrue(motor.onReverse());
    assertFalse(motor.onReverse());
    assertFalse(motor.onReverse());
    testCleanup();
  }

  test(onReverse_should_return_false_if_the_motor_is_set_forward) {
    motor.forward();
    assertFalse(motor.onReverse());
    assertFalse(motor.onReverse());
    testCleanup();
  }

// toggleDirection
  test(toggleDirection_should_flip_the_motor_from_forward_to_reverse) {
    motor.forward();
    motor.toggleDirection();
    assertTrue(revIsOn());
    assertFalse(fwdIsOn());
    testCleanup();
  }

  test(toggleDirection_should_flip_the_motor_from_reverse_to_forward) {
    motor.reverse();
    motor.toggleDirection();
    assertTrue(fwdIsOn());
    assertFalse(revIsOn());
    testCleanup();
  }

// update: only tested in real-time functions

// timedOn
  test(timedOn_should_turn_the_motor_on_for_the_specified_time_in_milliseconds) {
    motor.off();
    motor.timedOn(10);
    motor.update();
    // motor starts
    assertTrue(isOn());
    // half way through
    delay(5);
    motor.update();
    assertTrue(isOn());
    // time is almost up
    delay(3);
    motor.update();
    assertTrue(isOn());
    // should be expired
    delay(2);
    motor.update();
    assertFalse(isOn());
    testCleanup();
  }

// isOn
  test(isOn_should_return_true_when_the_motor_is_on) {
    motor.on();
    assertTrue(motor.isOn());
    testCleanup();
  }

  test(isOn_should_return_false_when_the_motor_is_off) {
    motor.off();
    assertFalse(motor.isOn());
    testCleanup();
  }

// isOff
  test(isOff_should_return_true_when_the_motor_is_off) {
    motor.off();
    assertTrue(motor.isOff());
    testCleanup();
  }

  test(isOff_should_return_false_when_the_motor_is_on) {
    motor.on();
    assertFalse(motor.isOff());
    testCleanup();
  }

// setSpeed
  unsigned long pulse1 = 0;
  unsigned long pulse2 = 0;

  void assertWithinTolerance(unsigned long value1, unsigned long value2, int tolerance_percent) {
    // +/- tolerance percent
    assertLessOrEqual(value1, (unsigned long)(value2 * float(1 + tolerance_percent / 100.0)));
    assertMoreOrEqual(value1, (unsigned long)(value2 * float(1 - tolerance_percent / 100.0)));
  }

  test(setSpeed_should_increase_the_speed_of_the_motor) {
    motor.setSpeed(50);
    pulse1 = getPulseTime();
    motor.setSpeed(200);
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    testCleanup();
  }

  test(setSpeed_should_decrease_the_speed_of_the_motor) {
    motor.setSpeed(225);
    pulse1 = getPulseTime();
    motor.setSpeed(75);
    pulse2 = getPulseTime();
    assertMore(pulse1, pulse2);
    testCleanup();
  }

  test(setSpeed_should_set_the_speed) {
    motor.setSpeed(100);
    pulse1 = getPulseTime();
    motor.setSpeed(200);
    pulse2 = getPulseTime();
    assertWithinTolerance(pulse1 * 2, pulse2, 10);
    testCleanup();
  }

  test(setSpeed_of_0_should_turn_off_the_motor) {
    motor.on();
    motor.setSpeed(0);
    assertTrue(isOff());
    assertTrue(motor.isOff());
    testCleanup();
  }

  test(setSpeed_of_255_should_turn_on_the_motor) {
    motor.off();
    motor.setSpeed(255);
    assertTrue(isOn());
    assertTrue(motor.isOn());
    testCleanup();
  }

// setSpeedPercent
  test(setSpeedPercent_should_set_the_speed_percentage) {
    motor.setSpeedPercent(45);
    pulse1 = getPulseTime();
    motor.setSpeedPercent(90);
    pulse2 = getPulseTime();
    assertWithinTolerance(pulse1 * 2, pulse2, 10);
    testCleanup();
  }

  test(setSpeedPercent_of_0_should_turn_off_the_motor) {
    motor.on();
    motor.setSpeedPercent(0);
    assertTrue(isOff());
    assertTrue(motor.isOff());
    testCleanup();
  }

  test(setSpeedPercent_of_100_should_turn_on_the_motor) {
    motor.off();
    motor.setSpeedPercent(100);
    assertTrue(isOn());
    assertTrue(motor.isOn());
    testCleanup();
  }

// getSpeed
  test(getSpeed_should_return_the_speed) {
    motor.setSpeed(123);
    assertEqual(motor.getSpeed(), 123);
    testCleanup();
  }

// getSpeedPercent
  test(getSpeedPercent_should_return_the_speed) {
    motor.setSpeed(51);
    assertEqual(motor.getSpeedPercent(), 20);
    testCleanup();
  }

  test(getSpeedPercent_should_return_the_speed_percentage) {
    motor.setSpeedPercent(50);
    assertEqual(motor.getSpeedPercent(), 50);
    testCleanup();
  }

// ramp
  test(ramp_should_increase_the_speed) {
    motor.setSpeed(20);
    pulse1 = getPulseTime();
    motor.ramp(255, 100);
    delay(30);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    pulse1 = pulse2;
    delay(30);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    delay(51);
    motor.update();
    assertTrue(isOn());
    testCleanup();
  }

  test(ramp_should_decrease_the_speed) {
    motor.setSpeed(200);
    pulse1 = getPulseTime();
    motor.ramp(0, 10);
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    pulse1 = pulse2;
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    delay(5);
    motor.update();
    assertTrue(isOff());
    testCleanup();
  }

  test(ramp_should_start_at_the_current_speed_and_end_at_the_target) {
    motor.setSpeed(200);
    delay(1);
    pulse1 = getPulseTime();
    motor.setSpeed(20);
    delay(1);
    pulse2 = getPulseTime();
    motor.ramp(200,10);
    motor.update();
    assertWithinTolerance(getPulseTime(), pulse2, 15);
    delay(10);
    motor.update();
    assertWithinTolerance(getPulseTime(), pulse1, 15);
    testCleanup();
  }

// rampPercent
  test(rampPercent_should_increase_the_speed_percentage) {
    motor.setSpeedPercent(15);
    pulse1 = getPulseTime();
    motor.rampPercent(100, 10);
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    pulse1 = pulse2;
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    delay(5);
    motor.update();
    assertTrue(isOn());
    testCleanup();
  }

  test(rampPercent_should_decrease_the_speed_percentage) {
    motor.setSpeedPercent(90);
    pulse1 = getPulseTime();
    motor.rampPercent(0, 10);
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    pulse1 = pulse2;
    delay(3);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    delay(5);
    motor.update();
    assertTrue(isOff());
    testCleanup();
  }

  test(rampPercent_should_start_at_the_current_speed_and_end_at_the_target_percentage) {
    motor.setSpeedPercent(90);
    pulse2 = getPulseTime();
    motor.setSpeedPercent(20);
    pulse1 = getPulseTime();
    motor.rampPercent(90,100);
    motor.update();
    assertWithinTolerance(getPulseTime(), pulse1, 15);
    delay(100);
    motor.update();
    assertWithinTolerance(getPulseTime(), pulse2, 15);
    testCleanup();
  }

// rampUp
  test(rampUp_should_increase_the_speed) {
    motor.setSpeed(20);
    pulse1 = getPulseTime();
    motor.rampUp(100);
    motor.update();
    delay(50);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    pulse1 = pulse2;
    delay(40);
    motor.update();
    pulse2 = getPulseTime();
    assertMore(pulse2, pulse1);
    delay(30);
    motor.update();
    assertTrue(isOn());
    testCleanup();
  }

// rampDown
  test(rampDown_should_decrease_the_speed) {
    motor.setSpeed(200);
    pulse1 = getPulseTime();
    motor.rampDown(100);
    motor.update();
    delay(50);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    pulse1 = pulse2;
    delay(40);
    motor.update();
    pulse2 = getPulseTime();
    assertLess(pulse2, pulse1);
    delay(30);
    motor.update();
    assertTrue(isOff());
    testCleanup();
  }

// onTargetSpeed
  test(onTargetSpeed_should_return_true_only_after_speed_is_achieved) {
    motor.ramp(255, 100);
    delay(50);
    motor.update();
    assertFalse(motor.onTargetSpeed());
    delay(51);
    motor.update();
    assertTrue(motor.onTargetSpeed());
    assertFalse(motor.onTargetSpeed());
    testCleanup();
  }

// setup and run tests
void setup() {
  testSetup();
  Serial.begin(115200);
  while(!Serial);
}

void testSetup() {
  pinMode(pwm_pin, INPUT);
  pinMode(fwd_pin, INPUT);
  pinMode(rev_pin, INPUT);
}

void loop() {
  Test::run();
}

void testCleanup() {
  // turn off the motor
  motor.off();
  // reset events
  motor.reverse();
  motor.onForward();
  motor.forward();
  motor.onReverse();
}