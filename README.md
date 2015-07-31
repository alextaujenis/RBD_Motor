#Arduino Motor Library
A simple, non-blocking, real-time Arduino library for controlling motors. It provides basic control along with more advanced features such as precision easing of motor power over relative time. Control an unlimited number of motors while seamlessly easing their speeds across dynamic transitions.

Example:

0. Tell a motor to spin at 30%.
0. Ask it to slow down to 25% over the course of 3 seconds.
0. Then, 1 second later change your mind and ask it to spin up to 80% over the course of 2 seconds.
0. The motor speed will transitions smoothly across all requests.
0. You can control many different motors like this at the same time.

#Installation
Download this Motor library and move it to your Arduino libraries folder. Also, there is a single dependency on a very light-weight Arduino timer library. Please install this library as well:

[Arduino Timer Library (required)](https://github.com/alextaujenis/Timer) <- dependency

#Example Sketch
Load up the example.ino to your Arduino and you can control a motor from text commands in a serial prompt connected at **11500 BAUD**. This example is set to control the Arduino LED 13, but you can change it to a motor. The command structure is simple and compressed. The entire protocol is essentially integers separated by commas with ; at the end. The first integer is to look up the command, then any integers after that are considered parameters to the command.

*This serial command interface was made for the example sketch and demonstration only; you should use the **Documentation** (farther below) to control motors for real within your program.

###Serial Commands for the Example Sketch
<hr />

####ON: Turn on the motor:

    1;

<hr />

####OFF: Turn off the motor:

    2;

<hr />

####TIMED_ON: Turn on the motor for 1 second:

    3,1000;

<hr />

####IS_ON: Is the motor on?

    4;

<hr />

####IS_OFF: Is the motor off?

    5;

<hr />

####GET_PWM: How fast is the motor running (0-255)?

    6;

<hr />

####GET__PWM__PERCENT: How fast is the motor running (0-100)?

    7;

<hr />

####SET_PWM: Make the motor go about half power (0-255):

    8,127;

<hr />

####SET__PWM__PERCENT: Make the motor go half power (0-100):

    9,50;

<hr />

####RAMP_UP: Ramp the motor up to full power in 3 seconds:

    10,3000;

<hr />

####RAMP_DOWN: Ramp the motor down to no power in 5 seconds:

    11,5000;

<hr />

####RAMP: Ramp the motor to about half power (0-255) in a quarter second:

    12,127,250;

<hr />

####RAMP_PERCENT: Ramp the motor to 3/4 power (0-100) in 9 seconds:

    13,75,9000;

<hr />

*This serial command interface above was made for the example sketch and demonstration only. You should use the public interface **Documentation** below to control motors for real within your program.

<hr />

#Documentation

##constructor(int pin)
Create a new motor and pass in the Arduino pin number.

##update()
This is a very fast and keeps the timed events on the motor running in real-time. This should be repeatedly called inside of loop().

##on()
Start the motor at full power.

##off()
Stop the motor.

##timedOn(int timeout)
Start the motor at full power and turn it off after the timeout (in milliseconds).

##isOn()
Returns true if the motor is running.

##isOff()
Returns true if the motor is not running.

##getPwm()
Returns a value from 0 - 255 for the current motor power.

##getPwmPercent()
Returns a value from 0 - 100 for the current motor power percentage.

##setPwm(int value)
Pass in a value from 0 - 255 to control the power of the motor.

##setPwmPercent(int value)
Pass in a value from 0 - 100 to control the power percentage of the motor. This is essentially the same as setPwm() but with a different input scale.

##rampUp(int timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current power to full power.

##rampDown(int timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current power to full stop.

##ramp(int value, int timeout)
Pass in a value from 0 - 255 to control the target power of the motor, and a timeout in milliseconds for how long it will take to ramp to that target power from the current power.

##rampPercent(int value, int timeout)
Pass in a value from 0 - 100 to control the target power percentage of the motor, and a timeout in milliseconds for how long it will take to ramp to that target power percentage from the current power. This is essentially the same as ramp() but with a different input scale.

<hr />

#License
This code is avaliable under the [MIT License](http://opensource.org/licenses/mit-license.php).