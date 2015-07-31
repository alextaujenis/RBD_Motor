#Arduino Motor Library
A simple, non-blocking, real-time Arduino library for motor control.

#Documentation

##Constructor(int pin)
Create a new motor and pass in the Arduino pin number.

##Update()
This is a very fast and keeps the motor running in real-time. Call this repeatedly inside of the loop() to make sure all of the timeout methods work correctly.

##on()
Start the motor at full speed.

##off()
Stop the motor.

##timedOn(int timeout)
Start the motor at full speed and turn it off after the timeout (in milliseconds).

##isOn()
Returns true if the motor is running.

##isOff()
Returns true if the motor is not running.

##speed()
Returns a value from 0 - 255 for the current motor speed.

##speedPercent()
Returns a value from 0 - 100 for the current motor speed percentage.

##pwm(int value)
Pass in a value from 0 - 255 to control the speed of the motor.

##pwmPercent(int value)
Pass in a value from 0 - 100 to control the speed percentage of the motor. This is essentially the same as pwm() but with a different input scale.

##rampUp(int timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current speed to full power.

##rampDown(int timeout)
Pass in a timeout in milliseconds for how long it will take to ramp from the current speed to full stop.

##ramp(int value, int timeout)
Pass in a value from 0 - 255 to control the target speed of the motor, and a timeout in milliseconds for how long it will take to ramp to that target speed from the current speed.

##rampPercent(int value, int timeout)
Pass in a value from 0 - 100 to control the target speed percentage of the motor, and a timeout in milliseconds for how long it will take to ramp to that target speed percentage from the current speed. This is essentially the same as ramp() but with a different input scale.