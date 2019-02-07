//
// Created by Nico Wittig on 2018-12-19.
//

#include "e_rainbow_shift.h"

e_rainbow_shift::e_rainbow_shift(light_element *le) : effect(le, EFFECT_NAME) {

}

e_rainbow_shift::~e_rainbow_shift() {

}

bool e_rainbow_shift::init() {

    for (int i = 0; i < le->get_num_leds(); i++) {
        le->leds[i] = CHSV(i * 255/le->get_num_leds(), 255, 255);
    }

    return true;
}

bool e_rainbow_shift::run() {
    shift(1);
    return false;
}
