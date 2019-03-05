//
// Created by Nico Wittig on 2019-03-03.
//

#include "e_meteor.hpp"

e_meteor::e_meteor(light_element *le, bool forward, uint8_t trail_decay) : effect(le, EFFECT_NAME) {
    this->forward = forward;
    this->trail_decay = trail_decay;
}

e_meteor::e_meteor(light_element *le, bool forward, uint8_t trail_decay, bool no_random) : effect(le, EFFECT_NAME) {
    this->forward = forward;
    this->trail_decay = trail_decay;
    this->no_random = no_random;
}


e_meteor::~e_meteor() {
}


bool e_meteor::init() {
    set_color(CHSV(190, 255, 0));
    return true;
}


bool e_meteor::run() {

    // catch exceptions
    meteor_position = modulo(meteor_position, le->get_num_leds());

    // fade out the trail
    for (int led = 0; led < le->get_num_leds(); led++) {
        if (no_random || random8()%2 == 0) {
            fade_var(&le->leds[led%le->get_num_leds()].val, 0, -trail_decay);
        }
    }

    // make the meteor full brightness
    le->leds[meteor_position].val = 255;

    // move meteor
    meteor_position += (forward) ? 1 : -1;

    return false;
}
