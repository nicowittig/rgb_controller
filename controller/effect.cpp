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

void effect::set_pixel(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
    this->le->leds[pixel] = rgb2hsv_approximate(CRGB(red, green, blue));
}

void effect::set_pixel(uint16_t pixel, CHSV color) {
    this->le->leds[pixel] = color;
}

void effect::set_pixel(uint16_t pixel, CRGB color) {
    this->le->leds[pixel] = rgb2hsv_approximate(color);
}

void effect::set_all(CHSV color) {
    //for (int led = 0; led < le->get_num_leds(); led++) le->leds[led] = color;
    this->le->set_all(color);
}

void effect::set_all(CRGB color) {
    //for (int led = 0; led < le->get_num_leds(); led++) le->leds[led] = rgb2hsv_approximate(color);
    this->le->set_all(color);
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

    if (direction == 0 || effect_index >= le->get_num_leds() || check_color_matching(&new_color)) {
        effect_index = 0;
        return true;
    } else {
        if (direction > 0) {
            le->leds[effect_index] = new_color;
            effect_index += direction;
        } else {
            le->leds[le->get_num_leds()-effect_index-1] = new_color;
            effect_index -= direction;
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
