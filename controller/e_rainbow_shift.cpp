//
// Created by Nico Wittig on 2018-12-19.
//

#include "e_rainbow_shift.h"

e_rainbow_shift::e_rainbow_shift(light_element *le) : effect(le) {

}

e_rainbow_shift::~e_rainbow_shift() {

}

bool e_rainbow_shift::init() {
    Serial.println("init: e_rainbow_shift");

    for (int i = 0; i < le->get_num_leds(); i++) {
        le->leds[i] = CHSV(i * 255/le->get_num_leds(), 255, 255);
    }

    return true;
}

bool e_rainbow_shift::run() {
    Serial.println("run: e_rainbow_shift");
    shift(1);
    return false;
}
