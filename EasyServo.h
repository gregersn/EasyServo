#ifndef EasyServo_h
#define EasyServo_h

#include "Servo.h"

class EasyServo: public Servo
{
    private:
        double delta_pos;
        int target_pos;
        double pos;
        unsigned long last_update;
        unsigned int speed;

    public:
        EasyServo();
        void set_speed(unsigned int s);
        unsigned int get_speed();
        double get_pos();

        void move(int pos);
        void move(int pos, unsigned int t);
        void update(unsigned long _time);

        bool is_moving();
};

#endif