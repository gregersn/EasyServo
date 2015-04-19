#ifndef EasyServo_h
#define EasyServo_h

#include "Servo.h"

class EasyServo: public Servo
{
    private:
        double delta_pos; // Ammount to move in each timestep
        int target_pos;   // The position we are moving towards
        double pos;       // The current position
        unsigned long last_update;  // The time when the servo was last updated
        unsigned int speed;         // The speed to move at
        bool moving;
        unsigned int _min;
        unsigned int _max;

    public:
        EasyServo();

        uint8_t attach(int pin); 
        uint8_t attach(int pin, int _min, int _max); // as above but also sets min and max values for writes. 

        void set_speed(unsigned int s);
        unsigned int get_speed();
        double get_pos();

        void write(int pos);

        void move(int pos);
        void move(int pos, unsigned int t);

        void moveMicroseconds(int value);
        void moveMicroseconds(int value, unsigned int t);

        void update(unsigned long _time);

        bool is_moving();
};

#endif