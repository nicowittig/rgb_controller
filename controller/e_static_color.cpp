//
// Created by Nico Wittig on 2019-02-07.
//

#include "e_static_color.h"

e_static_color::e_static_color(light_element *le, CHSV color) : effect(le, EFFECT_NAME) {
    this->color = color;
}

e_static_color::e_static_color(light_element *le, CRGB color) : effect(le, EFFECT_NAME) {
    this->color = rgb2hsv_approximate(color);
}

e_static_color::~e_static_color() {

}

bool e_static_color::init() {

    for (int i = 0; i < le->get_num_leds(); i++) {
        le->leds[i] = this->color;
    }

    return true;
}

bool e_static_color::run() {
    return false;
}
