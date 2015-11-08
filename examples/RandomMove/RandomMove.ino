#include <Servo.h>
#include <EasyServo.h>

EasyServo servo;


void setup() {
    Serial.begin(9600);
    servo.attach(9);
    servo.set_speed(5000);
    servo.write(15);
    delay(10);
    servo.move(165);
}

void loop() {
    if(!servo.is_moving()) {
        unsigned int new_pos = random(30, 165);
        Serial.print("Time: ");
        Serial.println(millis());
        Serial.print("New pos: ");
        Serial.println(new_pos);
        servo.move(new_pos);
    }

    servo.update(millis());
 }
