# NanoRelay

OVERVIEW

The Nano Relay is a simple input-output processor to monitor 1-3 inputs and generate 1-2 outputs, the primary one being the driving of a relay.  Our custom PCB uses an Arduino Nano 3.0 and a small relay.

The Arduino sketch should contain a Parameters section at the head with the following options, commented for the user:  (Note: each of these parameters also describes how it should work in the code’s main loop.)

INPUT

(the events that will trigger the output)

In 1 duration:  (duration of time that In 1 pin needs to be pulled low before it leads to a trigger event)
0=instant
otherwise, entry in ms

(Note: should trigger immediately after duration has been reached, not upon end/release of input signal)

In 1 delay:  (period of time after a trigger event that no further input from In 1 will be accepted, in ms)

In 2 duration:  (same as In 1 duration, but for In 2 pin)

In 2 delay:

In 2 multiple:  Number of discrete trigger events in In 2 pin before output is triggered.  

Analog In High Threshold:  (value on Analog In, in volts, that triggers output when reached or exceeded.  If blank, does not respond no matter how high the value)

Analog In Low Threshold:  (value on Analog In, in volts; triggers output if value is lower than this)




OUTPUT


Relay delay:  Upon trigger event, delay before relay is activated.)

Relay duration:  Time, in ms, that relay is activated.

Relay multiple:  Number of times the relay is activated after a single trigger event.  (“1”=default)

Relay interval:  Delay between multiple activations (if “Relay multiple” is >1)

Out delay:  Same as relay, but for Out pin.  Activation means sending 5V on the Out pin.

Out duration:

Out multiple:  

Out interval:

Output pause:  duration after the end of all outputs before any input is accepted.


CURRENT STATE:

The script was written but not tested because of the malfunctioning of the arduino. We need to order a new arduino in order to run and test the script to continue the project. I wrote this script with any prior arduino experience, so I expect it to need a lot of debugging and not work correctly. The IN2 is still not implemented, as in order to implement it, we need the rest to work. 




