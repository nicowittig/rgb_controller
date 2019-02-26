//
// Created by Nico Wittig on 2018-12-19.
//

#include "e_rainbow_shift.h"

e_rainbow_shift::e_rainbow_shift(light_element *le) : effect(le, EFFECT_NAME) {
}

e_rainbow_shift::~e_rainbow_shift() {
}

bool e_rainbow_shift::init() {

    for (int led = 0; led < le->get_num_leds(); led++) {
        le->leds[led] = CHSV(led * 255/le->get_num_leds(), 255, 255);
    }

    return true;
}

bool e_rainbow_shift::run() {
    shift(1);
    return false;
}
