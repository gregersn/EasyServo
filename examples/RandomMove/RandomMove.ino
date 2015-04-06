#include <Servo.h>
#include <EasyServo.h>

EasyServo servo;

void setup() {
    servo.attach(9);
    servo.set_speed(1000);
}


void loop() {
    if(!servo.is_moving()) {
        servo.move(random(0, 180));
    }

    servo.update(millis());
}
