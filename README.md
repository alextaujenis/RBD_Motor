#Arduino Motor Library
Control many motors in real-time without delay using commands like [on()](#on), [off()](#off), [timedOn()](#timedontimeout), and [ramp()](#rampvalue-timeout). Fire custom events when the motor has reached the target speed with [onTargetSpeed()](#ontargetspeed). Motors must be correctly wired to PWM enabled Arduino pins to work with this library.

##Real-Time Library

This real-time library requires that you manage the flow of your program without delay() or interrupts. Check out this [Arduino Timer Library](https://github.com/alextaujenis/RBD_Timer) if you are managing millis() by hand.

##Example Setup

0. Install this Motor Library and the [RBD::Timer Library](https://github.com/alextaujenis/RBD_Timer) dependency
0. Correctly wire and provide external power to a motor attached to Arduino PWM pin 3
0. Load the example sketch on to an Arduino
0. Watch the motor spin up and down without delay

**Example Sketch**:

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

#Documentation

##Public Methods

* [constructor(pin)](#constructorpin)
<hr />
* [on()](#on)
* [off()](#off)
* [setPwm(value)](#setpwmvalue)
* [setPwmPercent(value)](#setpwmpercentvalue)
<hr />
* [isOn()](#ison)
* [isOff()](#isoff)
* [getPwm()](#getpwm)
* [getPwmPercent()](#getpwmpercent)
* [isPwm(value)](#ispwmvalue)
* [isPwmPercent(value)](#ispwmpercentvalue)
<hr />
* [update()](#update)
* [timedOn(timeout)](#timedontimeout)
* [rampUp(timeout)](#rampuptimeout)
* [rampDown(timeout)](#rampdowntimeout)
* [ramp(value, timeout)](#rampvalue-timeout)
* [rampPercent(value, timeout)](#ramppercentvalue-timeout)
<hr />
* [onTargetSpeed()](#ontargetspeed)

##constructor(pin)
Create a new motor and pass in the Arduino pin number.

    RBD::Motor motor(3); // pwm pin 3

    void setup() {
      ...
    }

##on()
Start the motor at full speed.

    void setup() {
      motor.on();
    }

##off()
Stop the motor.

    void setup() {
      motor.off();
    }

##setPwm(value)
Pass in an integer from 0 - 255 to control the speed of the motor.

    void setup() {
      motor.setPwm(85); // one-third speed
    }

##setPwmPercent(value)
Pass in an integer from 0 - 100 to control the speed percentage of the motor. This is essentially the same as [setPwm()](#setpwmvalue) but with a smaller input scale.

    void setup() {
      motor.setPwmPercent(50); // half speed
    }

##isOn()
Returns true if the motor is running at 100% speed.

    void setup() {
      motor.on();
    }

    void loop() {
      Serial.println(motor.isOn());
    }

##isOff()
Returns true if the motor is running at 0% speed.

    void setup() {
      motor.off();
    }

    void loop() {
      Serial.println(motor.isOff());
    }

##getPwm()
Returns an integer from 0 - 255 for the current motor speed.

    void setup() {
      motor.setPwm(123);
    }

    void loop() {
      Serial.println(motor.getPwm());
    }

##getPwmPercent()
Returns an integer from 0 - 100 for the current motor speed percentage.

    void setup() {
      motor.setPwmPercent(45);
    }

    void loop() {
      Serial.println(motor.getPwmPercent());
    }

##isPwm(value)
Provide an integer from 0 to 255 and this will return true if it's equal to the current [getPwm()](#getpwm).

    void setup() {
      motor.ramp(99, 1000);
    }

    void loop() {
      motor.update()

      if(motor.onTargetSpeed()) {
        if(motor.isPwm(99)) {
          ...
        }
      }
    }

##isPwmPercent(value)
Provide an integer from 0 to 100 and this will return true if it's equal to the current [getPwmPercent()](#getpwmpercent).

    void setup() {
      motor.rampPercent(45, 1000);
    }

    void loop() {
      motor.update()

      if(motor.onTargetSpeed()) {
        if(motor.isPwmPercent(45)) {
          ...
        }
      }
    }

##update()
Keep the real-time functions processing with each loop().

    void loop() {
      motor.update();
    }

##timedOn(timeout)
Start the motor at full speed and turn it off after the specified time in milliseconds.

    void setup() {
      motor.timedOn(5000);
    }

    void loop() {
      motor.update();
    }

##rampUp(timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current speed to full speed with a linear transition.

    void setup() {
      motor.off();
      motor.rampUp(3000);
    }

    void loop() {
      motor.update();
    }

##rampDown(timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current speed to full stop with a linear transition.

    void setup() {
      motor.on();
      motor.rampDown(3000);
    }

    void loop() {
      motor.update();
    }

##ramp(value, timeout)
Pass in a value from 0 - 255 to control the target speed of the motor, and a timeout in milliseconds for how long it will take to ramp to that target speed from the current speed with a linear transition.

    void setup() {
      motor.ramp(85, 2000); // one-third speed in 2 seconds
    }

    void loop() {
      motor.update();
    }

##rampPercent(value, timeout)
Pass in a value from 0 - 100 to control the target speed of the motor, and a timeout in milliseconds for how long it will take to ramp to that target speed from the current speed with a linear transition. This is essentially the same as [ramp()](#rampvalue-timeout) but with a smaller input scale.

    void setup() {
      motor.rampPercent(50, 1000); // half speed in 1 second
    }

    void loop() {
      motor.update();
    }

##onTargetSpeed()
This method will return true once the motor hits the target speed set in any of the real-time methods. This method will return false until a new target speed is set (with a real-time method) and then achieved by the motor.

    void setup() {
      motor.off();
      motor.rampPercent(50, 5000);
    }

    void loop() {
      motor.update();

      if(motor.onTargetSpeed()) {
        // code only runs once per event
        Serial.println("Target Speed");
      }
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).