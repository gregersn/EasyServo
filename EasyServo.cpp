#include <EasyServo.h>
#include <Arduino.h>

EasyServo::EasyServo() {
    this->_min = MIN_PULSE_WIDTH;
    this->_max = MAX_PULSE_WIDTH;
    
    this->target_pos = DEFAULT_PULSE_WIDTH;
    this->pos = DEFAULT_PULSE_WIDTH;
    this->moving = false;
    this->last_update = 0;

    this->write(this->pos);
    this->set_speed(1000);
}

uint8_t EasyServo::attach(int pin) {
    /*Serial.println(MIN_PULSE_WIDTH);
    Serial.println(MAX_PULSE_WIDTH);*/
    return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t EasyServo::attach(int pin, int _min, int _max) {
    /*Serial.println("Attach-2");
    Serial.println(_min);
    Serial.println(_max);*/
    this->_min = _min;
    this->_max = _max;
    /*Serial.println(this->_min);
    Serial.println(this->_max);*/
    return Servo::attach(pin, _min, _max);
}

void EasyServo::set_speed(unsigned int s) {
    /*
        Let a speed of 1000 indicate 
        a one second duration of movement from one extreme
        to the other
    */
    this->speed = s;
}

unsigned int EasyServo::get_speed() {
    return this->speed;
}

int EasyServo::get_pos() {
    return this->pos;
}

int EasyServo::check_pos(int n_pos) {
    if(n_pos < this->_min) {
        if(n_pos < 0) n_pos = 0;
        if(n_pos > 180) n_pos = 180;
        n_pos = map(n_pos, 0, 180, this->_min, this->_max);
    }
    return n_pos;    
}

void EasyServo::write(int n_pos) {
    this->writeMicroseconds(this->check_pos(n_pos));
}

void EasyServo::writeMicroseconds(int n_pos) {
    this->pos = n_pos;
    this->target_pos = n_pos;
    this->moving = false;
    this->last_update = millis();
    this->duration = 0;
    Servo::writeMicroseconds(n_pos);
}

void EasyServo::move(int n_pos) {
    n_pos = this->check_pos(n_pos);
    double length = abs(n_pos - this->pos);
    double max_length = abs(this->_max - this->_min);

    double duration = (this->speed * length) / max_length;

    this->move(n_pos, duration);
}

void EasyServo::move(int n_pos, unsigned int t) {
    n_pos = this->check_pos(n_pos);
    if(n_pos == target_pos) {
        return;
    }
    this->prev_pos = this->target_pos;
    this->target_pos = n_pos;
    this->duration = t;
    this->starttime = millis();
    this->moving = true;
    this->update(millis());
}


void EasyServo::update(unsigned long _time) {
    long delta = 0;

    /*
    // Currently not used for anything sensible.
    if(_time < this->last_update) {
        // Handle overflow of time
        Serial.println("Time overflow");
        delta = (0xffffffff - this->last_update) + _time;
    }
    else {
        delta = _time - this->last_update;
    }*/

    delta = _time - this->starttime;

    if(delta >= this->duration) {
        this->pos = this->target_pos;
        this->moving = false;
    } else {
        this->pos = map(delta, 0, this->duration, this->prev_pos, this->target_pos);
    }

    Servo::writeMicroseconds((unsigned int)this->pos);
    this->last_update = _time;

    return;
}


bool EasyServo::is_moving() {
    return this->moving;
}
