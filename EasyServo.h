#ifndef EasyServo_h
#define EasyServo_h

#include "Servo.h"

class EasyServo: public Servo
{
    private:
        double delta_pos; // Ammount to move in each timestep
        unsigned int prev_pos; //
        double pos;       // The current position
        unsigned int target_pos;   // The position we are moving towards
        unsigned long last_update;  // The time when the servo was last updated
        unsigned int speed;         // The speed to move at
        bool moving;
        unsigned int _min;
        unsigned int _max;
        unsigned long starttime;
        unsigned int duration;

        int check_pos(int n_pos);

    public:
        EasyServo();

        uint8_t attach(int pin); 
        uint8_t attach(int pin, int _min, int _max); // as above but also sets min and max values for writes. 

        // Set the speed of the servo movements
        void set_speed(unsigned int s);

        // Get current servo speed
        unsigned int get_speed();

        // Get (internal) position of servo
        int get_pos();

        // These work as the original servo writes, no limitation on speed
        void write(int pos); // If value < 200 assume degrees, else microseconds
        void writeMicroseconds(int value);

        // Moves the servoes at the assigned speed
        void move(int pos);
        void move(int pos, unsigned int t);
        //void moveMicroseconds(int pos);
        //void moveMicroseconds(int pos, unsigned int t);

        // Update with current time to move the servo
        void update(unsigned long _time);

        // Return true if the servo has not reached latest destination
        bool is_moving();
};

#endif