//
// Created by Nico Wittig on 2018-12-14.
//

#include "effect.h"

effect::effect(light_element *le) {
    this->le = le;
}

bool effect::check_color_matching(CHSV *color) {
    for (int i = 0; i < this->le->get_num_leds(); i++) {
        if (this->le->leds[i] != *color) return false;
    }
    return true;
}

void effect::set_pixel(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
    this->le->leds[pixel] = rgb2hsv_approximate(CRGB(red, green, blue));
}

void effect::shift(int16_t direction) {
    if (direction > 0) {
        CHSV save_color = this->le->leds[this->le->get_num_leds() -1];

        for (int i = this->le->get_num_leds() -1; i >= 1; i--) {
            this->le->leds[i] = this->le->leds[i-1];
        }

        this->le->leds[0] = save_color;
        shift(--direction);
    } else if (direction < 0) {
        CHSV save_color = this->le->leds[0];

        for (int i = 0; i < this->le->get_num_leds(); i++) {
            this->le->leds[i] = this->le->leds[i+1];
        }

        this->le->leds[this->le->get_num_leds()-1] = save_color;
        shift(++direction);
    } else {
        return;
    }
}

void effect::shift_hue(int16_t direction) {

    if (direction > 0) {
        uint8_t save_hue = this->le->leds[this->le->get_num_leds() -1].hue;

        for (int i = this->le->get_num_leds() -1; i >= 1; i--) {
            this->le->leds[i].hue = this->le->leds[i-1].hue;
        }

        this->le->leds[0].hue = save_hue;
        shift_hue(--direction);
    } else if (direction < 0) {
        uint8_t save_hue = this->le->leds[0].hue;

        for (int i = 0; i < this->le->get_num_leds(); i++) {
            this->le->leds[i].hue = this->le->leds[i+1].hue;
        }

        this->le->leds[this->le->get_num_leds()-1].hue = save_hue;
        shift_hue(++direction);
    } else {
        return;
    }

}

bool effect::wipe(CHSV new_color, int8_t direction) {
    if (direction == 0 || this->effect_index >= this->le->get_num_leds() || check_color_matching(&new_color)) {
        this->effect_index = 0;
        return true;
    } else {
        if (direction > 0) {
            this->le->leds[this->effect_index] = new_color;
            this->effect_index += direction;
        } else {
            this->le->leds[this->le->get_num_leds()-this->effect_index-1] = new_color;
            this->effect_index -= direction;
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

bool effect::fade(CHSV *new_color, int8_t step) {
    bool all_colors_ready = true;

    for (int i = 0; i < this->le->get_num_leds(); i++) {

        if (!fade_manual(&le->leds[i].hue, new_color->hue, step)) all_colors_ready = false;

        if (!fade_manual(&le->leds[i].sat, new_color->sat,
                                (le->leds[i].sat > new_color->sat) ? -abs(step) : abs(step))) {
            all_colors_ready = false;
        }

        if (!fade_manual(&le->leds[i].val, new_color->val,
                                (le->leds[i].val > new_color->val) ? -abs(step) : abs(step))) {
            all_colors_ready = false;
        }
    }

    return all_colors_ready;
}
