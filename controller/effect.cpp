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

// region effect helper

bool effect::check_color_matching(CHSV *color, uint16_t begin_led, uint16_t end_led) {

    // Catch exceptions
    if (begin_led > end_led) { // first led after second -> switch leds
        uint16_t led = begin_led;
        begin_led = end_led;
        end_led = led;
    }

    for (uint16_t led = begin_led; led <= end_led; led++) {
        if (this->le->leds[led] != *color) return false;
    }

    return true;
}


bool effect::check_color_matching(CHSV *color) {
    return check_color_matching(color, 0, le->get_num_leds()-1);
}


CHSV effect::get_pixel_gradient(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t area_length,
                                uint16_t index_led) {

    // calculate variable values
    float diff_sat = (float) (end_color.sat-begin_color.sat)/(area_length-1);
    float diff_val = (float) (end_color.val-begin_color.val)/(area_length-1);
    float diff_hue;

    if (hue_cycle_forward) {
        diff_hue = (float) ((uint8_t) (end_color.hue-begin_color.hue))/(area_length-1);
    } else {
        diff_hue = (float) (-(uint8_t) (begin_color.hue-end_color.hue))/(area_length-1);
    }

    return CHSV(
            begin_color.hue+index_led*diff_hue,
            begin_color.sat+index_led*diff_sat,
            begin_color.val+index_led*diff_val);
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
    uint16_t area_length = end_led-begin_led+1;

    // set leds to new colors
    for (uint16_t i = 0; i < area_length; i++) {
        uint16_t current_led = begin_led + i;
        le->leds[current_led] = get_pixel_gradient(begin_color, end_color, hue_cycle_forward, area_length, i);
    }

}


void effect::set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led,
                       uint8_t cycles, bool forward_only) {

    // calculate variable values
    int area_length = end_led-begin_led+1;
    float cycle_length = (float) area_length/cycles;

    // call set_color for all cycles
    for (uint8_t c = 0; c < cycles; c++) {
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
    for (uint16_t led = 0; led < this->le->get_num_leds(); led++) {
        le->leds[led].hue += value;
    }
}


void effect::shift(int16_t direction) {
    if (direction > 0) {
        CHSV save_color = this->le->leds[this->le->get_num_leds() -1];

        for (uint16_t led = this->le->get_num_leds() -1; led >= 1; led--) {
            this->le->leds[led] = this->le->leds[led-1];
        }

        this->le->leds[0] = save_color;

        shift(--direction);
    } else if (direction < 0) {
        CHSV save_color = this->le->leds[0];

        for (uint16_t led = 0; led < this->le->get_num_leds(); led++) {
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


bool effect::wipe(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led,
                  int8_t direction) {

    if (begin_led > end_led) { // first led after second -> switch leds
        uint16_t led = begin_led;
        begin_led = end_led;
        end_led = led;
    }

    if (direction == 0) {
        return true;
    } else {

        // calculate variable values
        uint16_t area_length = abs(end_led-begin_led)+1;
        uint16_t max = 0;
        uint16_t min = 0u-1;

        for (uint16_t i = begin_led; i <= end_led; i++) {
            if (le->leds[i] != get_pixel_gradient(begin_color, end_color, hue_cycle_forward, area_length, i)) {
                if (i < min) min = i;
                if (i > max) max = i;
            }
        }

        if (direction > 0) {
            //le->leds[min] = new_color;
            for (int16_t j = 0; j < direction && min+j <= end_led; j++)
                le->leds[min+j] = get_pixel_gradient(begin_color, end_color, hue_cycle_forward, area_length, min+j-begin_led);
        } else {
            //le->leds[max] = new_color;
            for (int16_t j = 0; j > direction && ((int16_t) max)+j >= ((int16_t) begin_led); j--)
                le->leds[max+j] = get_pixel_gradient(begin_color, end_color, hue_cycle_forward, area_length, max+j-begin_led);
        }

    }

    return false;
}


bool effect::wipe(CHSV new_color, uint16_t begin_led, uint16_t end_led, int8_t direction) {
    return wipe(new_color, new_color, true, begin_led, end_led, direction);
}


bool effect::wipe(CHSV new_color, int8_t direction) {
    return wipe(new_color, 0, le->get_num_leds()-1, direction);
}


bool effect::fade_var(uint8_t *var, uint8_t end, int8_t step) {
    //Serial.print(step);
    if (step == 0 || *var == end) return true;

    *var += step;

    /*
    if ((step > 0 && *var >= end && *var < (uint8_t) (end+step))
        || step < 0 && (*var <= end || *var > (uint8_t) (end+step))) {
    */
    if ((step > 0 && *var > (uint8_t) (end-step) && *var <= end)
        || (step < 0 && *var < (uint8_t) (end-step) && *var >= end)) {

        *var = end;
        return true;
    }

    return false;
}


bool effect::fade(CHSV new_color, uint16_t pixel, uint8_t step) {

    // calculate variable values
    bool pixel_ready = true;
    int diff = (int) new_color.hue - (int) le->leds[pixel].hue;
    bool pos_step = (abs(diff) <= 128) == (diff >= 0);

    // fade the hue, sat and val
    if (!fade_var(&le->leds[pixel].hue, new_color.hue, (pos_step) ? step : -step))
        pixel_ready = false;

    if (!fade_var(&le->leds[pixel].sat, new_color.sat,
                  (le->leds[pixel].sat > new_color.sat) ? -step : step))
        pixel_ready = false;

    if (!fade_var(&le->leds[pixel].val, new_color.val,
                  (le->leds[pixel].val > new_color.val) ? -step : step))
        pixel_ready = false;

    return pixel_ready;
}


bool effect::fade(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led,
                  int8_t step) {

    // calculate variable values
    uint16_t area_length = end_led-begin_led+1;
    bool all_pixels_ready = true;

    for (int led = begin_led; led <= end_led; led++) {
        if (!fade(get_pixel_gradient(begin_color, end_color, hue_cycle_forward, area_length, led-begin_led), led, step)) all_pixels_ready = false;
    }

    return all_pixels_ready;
}


bool effect::fade(CHSV new_color, uint16_t begin_led, uint16_t end_led, int8_t step) {
    return fade(new_color, new_color, true, begin_led, end_led, step);
}


bool effect::fade(CHSV new_color, int8_t step) {
    return fade(new_color, 0, le->get_num_leds()-1, step);
}

// endregion