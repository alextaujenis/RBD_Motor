#Arduino Motor Library
A simple, non-blocking, real-time Arduino library for controlling motors. It provides basic control along with more advanced features such as precision easing of motor power over relative time. Control an (almost) unlimited number of motors while seamlessly easing their speeds across dynamic transitions.

##Example

0. Tell a motor to spin at 30%.
0. Ask it to slow down to 25% over the course of 3 seconds.
0. Then, 1 second later change your mind and ask it to spin up to 80% over the course of 2 seconds.
0. The motor speed will transition smoothly across all requests.
0. You can control many motors at the same time, all with unique parameters.

##How does it work?

    #include <RBD_Timer.h>
    #include <RBD_Motor.h>

    RBD::Motor motor1(3); // pwm pin 3
    RBD::Motor motor2(5); // pwm pin 5

    void loop() {
      // keep moving in real-time
      motor1.update();
      motor2.update();

      // call the documented Motor library commands here and interact in real-time
      // you must manage your program flow without delay() to keep the loop moving
      // either manage millis() by hand, or check out the Timer library below
    }


#Installation
Download and install this Arduino Motor library along with the Arduino Timer library below:

[Arduino Timer Library (required)](https://github.com/alextaujenis/RBD_Timer) <- dependency

The Motor library requires the Timer library, but you are not required to use the Timer functions in your own sketchs. **Beware:** you need to keep the loop() moving for the Motor timed functions to work, and you **can't use delay()**. If you are managing millis() by hand; you should look into using the Timer [library functions](https://github.com/alextaujenis/RBD_Timer#arduino-timer-library) in your own sketches to simplify things.

#Documentation

##Public Methods

* [constructor(pin)](#constructorpin)
* [update()](#update)
* [on()](#on)
* [off()](#off)
* [timedOn(timeout)](#timedontimeout)
* [isOn()](#ison)
* [isOff()](#isoff)
* [getPwm()](#getpwm)
* [getPwmPercent()](#getpwmpercent)
* [setPwm(value)](#setpwmvalue)
* [setPwmPercent(value)](#setpwmpercentvalue)
* [rampUp(timeout)](#rampuptimeout)
* [rampDown(timeout)](#rampdowntimeout)
* [ramp(value, timeout)](#rampvalue-timeout)
* [rampPercent(value, timeout)](#ramppercentvalue-timeout)

##constructor(pin)
Create a new motor and pass in the Arduino pin number.

##update()
This is very fast and keeps the timed events on the motor running in real-time. This should be repeatedly called inside of loop().

##on()
Start the motor at full power.

##off()
Stop the motor.

##timedOn(timeout)
Start the motor at full power and turn it off after the specified time in milliseconds.

##isOn()
Returns true if the motor is running.

##isOff()
Returns true if the motor is not running.

##getPwm()
Returns a value from 0 - 255 for the current motor power.

##getPwmPercent()
Returns a value from 0 - 100 for the current motor power percentage.

##setPwm(value)
Pass in a value from 0 - 255 to control the power of the motor.

##setPwmPercent(value)
Pass in a value from 0 - 100 to control the power percentage of the motor. This is essentially the same as setPwm() but with a smaller input scale.

##rampUp(timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current power to full power.

##rampDown(timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current power to full stop.

##ramp(value, timeout)
Pass in a value from 0 - 255 to control the target power of the motor, and a timeout in milliseconds for how long it will take to ramp to that target power from the current power.

##rampPercent(value, timeout)
Pass in a value from 0 - 100 to control the target power percentage of the motor, and a timeout in milliseconds for how long it will take to ramp to that target power percentage from the current power. This is essentially the same as ramp() but with a smaller input scale.


#Example Sketch
Load the [example.ino](/blob/master/example/example.ino) to your Arduino and you can control a motor (actually led 13 by default) from text commands in a serial prompt connected at **115200 BAUD**.

**The serial interface below only controls the example sketch. Read the [Documentation](#documentation) to control motors for real!**

The entire example serial protocol is essentially integers separated by commas with ; at the end. The first integer is to look up the command, then any integers after that are considered parameters to the command.

<hr />

####1 ON: Turn on the motor:

    1;

<hr />

####2 OFF: Turn off the motor:

    2;

<hr />

####3 TIMED_ON: Turn on the motor for 1 second:

    3,1000;

<hr />

####4 IS_ON: Is the motor on?

    4;

<hr />

####5 IS_OFF: Is the motor off?

    5;

<hr />

####6 GET_PWM: How fast is the motor running (0-255)?

    6;

<hr />

####7 GET\_PWM\_PERCENT: How fast is the motor running (0-100)?

    7;

<hr />

####8 SET_PWM: Make the motor go about half power (0-255):

    8,127;

<hr />

####9 SET\_PWM\_PERCENT: Make the motor go half power (0-100):

    9,50;

<hr />

####10 RAMP_UP: Ramp the motor up to full power in 3 seconds:

    10,3000;

<hr />

####11 RAMP_DOWN: Ramp the motor down to no power in 5 seconds:

    11,5000;

<hr />

####12 RAMP: Ramp the motor to about half power (0-255) in a quarter second:

    12,127,250;

<hr />

####13 RAMP_PERCENT: Ramp the motor to 3/4 power (0-100) in 9 seconds:

    13,75,9000;

<hr />

**The serial interface above only controls the example sketch. Read the [Documentation](#documentation) to control motors for real!**

<hr />

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).