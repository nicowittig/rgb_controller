//
// Created by Nico Wittig on 2018-12-14.
//

#include "effect.h"


effect::effect(light_element *le, char *name) {
    this->le = le;
    this->name = name;
}


effect::~effect() {
}


char* effect::getName() {
    return this->name;
}


bool effect::check_color_matching(CHSV *color) {

    for (int led = 0; led < this->le->get_num_leds(); led++) {
        if (this->le->leds[led] != *color) return false;
    }

    return true;
}

//region color setter

void effect::set_pixel(uint16_t pixel, CHSV color) {
    this->le->leds[pixel] = color;
}


void effect::set_pixel(uint16_t pixel, CRGB color) {
    this->le->leds[pixel] = rgb2hsv_approximate(color);
}


void effect::set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led) {

    // Catch exceptions
    if (begin_led == end_led) { // only one led -> set to begin color
        le->leds[begin_led] = begin_color;
        return;
    } else if (begin_led > end_led) { // first led after second -> switch leds
        uint16_t led = begin_led;
        begin_led = end_led;
        end_led = led;
    }

    // calculate variable values
    uint16_t leds_to_serve = end_led-begin_led+1;
    float diff_sat = (float) (end_color.sat-begin_color.sat)/(leds_to_serve-1);
    float diff_val = (float) (end_color.val-begin_color.val)/(leds_to_serve-1);
    float diff_hue;

    if (hue_cycle_forward) {
        diff_hue = (float) ((uint8_t) (end_color.hue-begin_color.hue))/(leds_to_serve-1);
    } else {
        diff_hue = (float) (-(uint8_t) (end_color.hue-begin_color.hue))/(leds_to_serve-1);
    }

    // set leds to new colors
    for (int i = 0; i < leds_to_serve; i++) {
        uint16_t current_led = begin_led + i;

        le->leds[current_led].hue = begin_color.hue + i*diff_hue;
        le->leds[current_led].sat = begin_color.sat + i*diff_sat;
        le->leds[current_led].val = begin_color.val + i*diff_val;
    }

}


void effect::set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led,
                       uint8_t cycles, bool forward_only) {

    // calculate variable values
    int leds_to_serve = end_led-begin_led+1;
    float cycle_length = (float) leds_to_serve/cycles;

    // call set_color for all cycles
    for (int c = 0; c < cycles; c++) {
        if (forward_only || c%2 == 0) {
            set_color(begin_color, end_color, hue_cycle_forward, begin_led+c*cycle_length, begin_led+(c+1)*cycle_length-1);
        } else {
            set_color(end_color, begin_color, !hue_cycle_forward, begin_led+c*cycle_length, begin_led+(c+1)*cycle_length-1);
        }
    }

}


void effect::set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led,
                       uint8_t cycles) {
    set_color(begin_color, end_color, hue_cycle_forward, begin_led, end_led, cycles, true);
}


void effect::set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward) {
    set_color(begin_color, end_color, hue_cycle_forward, 0, le->get_num_leds()-1);
}


void effect::set_color(CHSV begin_color, CHSV end_color) {
    set_color(begin_color, end_color, true);
}


void effect::set_color(CHSV color) {
    set_color(color, color);
}

//endregion

void effect::increase_hue(int16_t value) {
    for (int led = 0; led < this->le->get_num_leds(); led++) {
        le->leds[led].hue += value;
    }
}


void effect::shift(int16_t direction) {
    if (direction > 0) {
        CHSV save_color = this->le->leds[this->le->get_num_leds() -1];

        for (int led = this->le->get_num_leds() -1; led >= 1; led--) {
            this->le->leds[led] = this->le->leds[led-1];
        }

        this->le->leds[0] = save_color;
        shift(--direction);
    } else if (direction < 0) {
        CHSV save_color = this->le->leds[0];

        for (int led = 0; led < this->le->get_num_leds(); led++) {
            this->le->leds[led] = this->le->leds[led+1];
        }

        this->le->leds[this->le->get_num_leds()-1] = save_color;
        shift(++direction);
    } else {
        return;
    }
}


void effect::shift_hue(int16_t direction) {

    if (direction > 0) {
        uint8_t save_hue = le->leds[le->get_num_leds() -1].hue;

        for (int led = le->get_num_leds() -1; led >= 1; led--) {
            le->leds[led].hue = le->leds[led-1].hue;
        }

        le->leds[0].hue = save_hue;
        shift_hue(--direction);
    } else if (direction < 0) {
        uint8_t save_hue = le->leds[0].hue;

        for (int led = 0; led < le->get_num_leds(); led++) {
            le->leds[led].hue = le->leds[led+1].hue;
        }

        le->leds[le->get_num_leds()-1].hue = save_hue;
        shift_hue(++direction);
    } else {
        return;
    }

}


bool effect::wipe(CHSV new_color, int8_t direction) {

    if (direction == 0 || wipe_index >= le->get_num_leds() || check_color_matching(&new_color)) {
        wipe_index = 0;
        return true;
    } else {
        if (direction > 0) {
            le->leds[wipe_index] = new_color;
            wipe_index += direction;
        } else {
            le->leds[le->get_num_leds()-wipe_index-1] = new_color;
            wipe_index -= direction;
        }
    }

    return false;
}


bool effect::fade_manual(uint8_t *var, uint8_t end, int8_t step) {
    if (step == 0 || *var == end) return true;

    *var += step;

    /*
    if ((step > 0 && *var >= end && *var < (uint8_t) (end+step))
        || step < 0 && (*var <= end || *var > (uint8_t) (end+step))) {
    */
    if ((step > 0 && *var > (uint8_t) (end-step))
        || (step < 0 && *var < (uint8_t) (end-step))) {

        *var = end;
        return true;
    }

    return false;
}


bool effect::fade(CHSV new_color, int8_t step) {
    bool all_colors_ready = true;

    for (int led = 0; led < this->le->get_num_leds(); led++) {

        if (!fade_manual(&le->leds[led].hue, new_color.hue, step)) all_colors_ready = false;

        if (!fade_manual(&le->leds[led].sat, new_color.sat,
                                (le->leds[led].sat > new_color.sat) ? -abs(step) : abs(step))) {
            all_colors_ready = false;
        }

        if (!fade_manual(&le->leds[led].val, new_color.val,
                                (le->leds[led].val > new_color.val) ? -abs(step) : abs(step))) {
            all_colors_ready = false;
        }
    }

    return all_colors_ready;
}
