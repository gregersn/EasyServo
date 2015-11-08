EasyServo
----------

A small wrapper-class for the Arduino(TM) Servo-control to have speed control
and (hopefully when I get so far) easing of servo movement. 

Provided as-is


Usage:

Instead of the regular Servo instance, make an EasyServo, then attach
to pin as usual. 

To move the servo use servo->move(pos); and make sure that servo->update(millis())
is called often to update the position. The update function can maybe be moved
to a timer or something. A side effect of not updating often might be jerky motion.

