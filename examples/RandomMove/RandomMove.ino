#include <Servo.h>
#include <EasyServo.h>

EasyServo servo;


void setup() {
    Serial.begin(9600);
    servo.attach(9);
    servo.set_speed(5000);
    servo.write(22);
}

void loop() {
    //Serial.println("Hey");
    if(!servo.is_moving()) {
        unsigned int new_pos = random(15, 165);
        Serial.println(new_pos);
        //servo.move(new_pos);
        servo.move(new_pos);
        //Serial.println("Hooh!");
    }

    servo.update(millis());
    //delay(15);
    //Serial.println("Yo!");
    //delay(250);
}
