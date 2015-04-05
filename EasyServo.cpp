#include <EasyServo.h>
#include <Arduino.h>

void EasyServo::set_speed(unsigned int s) {
    /*
        Let a speed of 1000 indicate 
        a one second duration of movement from one extreme
        to the other
    */
    this->speed = s;
    this->delta_pos = 180.0 / (double)s;
}

unsigned int EasyServo::get_speed() {
    return this->speed;
}

double EasyServo::get_pos() {
    return this->pos;
}

void EasyServo::move(int pos) {
    this->target_pos = pos;
    this->update(millis());
}

void EasyServo::update(unsigned long _time) {
    long delta = 0;
    if(_time < this->last_update) {
        // Handle overflow of time
        delta = (0xffffffff - this->last_update) + _time;
    }
    else {
        delta = _time - this->last_update;
    }
    if((int)this->pos > this->target_pos)
    {
        this->pos -= delta * this->delta_pos;
        if((int)this->pos < this->target_pos) {
            this->pos = this->target_pos;
        }
    }
    else if((int)this->pos < this->target_pos) {
        this->pos += delta * this->delta_pos;
        if((int)this->pos > this->target_pos) {
            this->pos = this->target_pos;
        }
    }

    this->write((int)this->pos);

    this->last_update = _time;
}

