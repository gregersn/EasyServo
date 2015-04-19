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
    //Serial.println("Set speed");
    this->speed = s;
    this->delta_pos = abs(this->_max - this->_min) / (float)s;
    /*Serial.println(this->_max);
    Serial.println(this->_min);*/
    //Serial.print("Delta pos: ");
    //Serial.println(this->delta_pos);
}

unsigned int EasyServo::get_speed() {
    return this->speed;
}

double EasyServo::get_pos() {
    return this->pos;
}

void EasyServo::write(int n_pos) {
    if(n_pos < this->_min) {
        n_pos = map(n_pos, 0, 180, this->_min, this->_max);
    }
    this->pos = n_pos;
    this->target_pos = n_pos;
    this->moving = false;
    this->last_update = millis();
    Servo::write(n_pos);
}

void EasyServo::move(int n_pos) {
    if(n_pos < this->_min) {
        n_pos = map(n_pos, 0, 180, this->_min, this->_max);
    }
    this->last_update = millis();
    this->target_pos = n_pos;
    this->moving = true;
    this->update(millis());
}

void EasyServo::move(int n_pos, unsigned int t) {
    if(n_pos < this->_min) {
        n_pos = map(n_pos, 0, 180, this->_min, this->_max);
    }
    // Moves the servo to the new pos using the time specified
    // That will override and set a new speed
    int dx = abs(n_pos - this->pos); // The distance to move in pulse widths
    unsigned int speed = ((this->_max - this->_min) * t) / dx;
    this->set_speed(speed);
    this->move(n_pos);
}


void EasyServo::update(unsigned long _time) {
    //Serial.println("UPDATE!");
    long delta = 0;
    if(_time < this->last_update) {
        // Handle overflow of time
        Serial.println("Time overflow");
        delta = (0xffffffff - this->last_update) + _time;
    }
    else {
        delta = _time - this->last_update;
    }

    if(delta < 10)
    {
        // Don't update too often, this should maybe be speed based?
        //Serial.println("Not long enough");
        return; 
    }

    if((unsigned int)this->pos > this->target_pos) 
    {
        this->pos -= (delta * this->delta_pos);

        if((int)this->pos <= this->target_pos) 
        {
            this->pos = this->target_pos;
            this->moving = false;
        }
    }
    else if((unsigned int)this->pos < this->target_pos) 
    {
        this->pos += (delta * this->delta_pos);
        if((int)this->pos >= this->target_pos) 
        {
            this->pos = this->target_pos;
            this->moving = false;
        }
    }
    else
    {
        this->moving = false;
    }

    this->last_update = _time;
    //if(!this->moving) return;
    //Serial.println(this->pos);
    Servo::writeMicroseconds((unsigned int)this->pos);

}


bool EasyServo::is_moving() {
    return this->moving;
}
