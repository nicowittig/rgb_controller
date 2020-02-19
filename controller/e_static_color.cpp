//
// Created by Nico Wittig on 2019-02-07.
//

#include "e_static_color.hpp"

e_static_color::e_static_color(light_element *le, CHSV color) : effect(le, EFFECT_NAME) {
    this->begin_color = color;
    this->end_color = color;
}

e_static_color::e_static_color(light_element *le, CHSV begin_color, CHSV end_color) : effect(le, EFFECT_NAME) {
    this->begin_color = begin_color;
    this->end_color = end_color;
}

e_static_color::e_static_color(light_element *le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward) : effect(le, EFFECT_NAME) {
    this->begin_color = begin_color;
    this->end_color = end_color;
    this->hue_cycle_forward = hue_cycle_forward;
}

e_static_color::e_static_color(light_element *le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward,
                               uint8_t cycles) : effect(le, EFFECT_NAME) {
    this->begin_color = begin_color;
    this->end_color = end_color;
    this->hue_cycle_forward = hue_cycle_forward;
    this->cycles = cycles;
}

e_static_color::e_static_color(light_element *le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward,
                               uint8_t cycles, bool forward_only) : effect(le, EFFECT_NAME) {
    this->begin_color = begin_color;
    this->end_color = end_color;
    this->hue_cycle_forward = hue_cycle_forward;
    this->cycles = cycles;
    this->forward_only = forward_only;
}

e_static_color::~e_static_color() {
}

bool e_static_color::init() {
    set_color(begin_color, end_color, hue_cycle_forward, 0, le->get_num_leds()-1, cycles, forward_only);
    return true;
}

bool e_static_color::run() {
    return false;
}
