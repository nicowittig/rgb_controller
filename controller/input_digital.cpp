//
// Created by Nico Wittig on 2018-12-13.
//

#include "input_digital.h"


input_digital::input_digital(uint8_t input_pin, bool pullup, bool invert) :input(input_pin, invert) {
    this->pullup = pullup;
    pinMode(input_pin, (pullup) ? INPUT_PULLUP : INPUT);
}


bool input_digital::digital_read() {
    return digitalRead(input_pin) != invert;
}


void input_digital::print_to_serial() {
    Serial.println(digital_read());
}
