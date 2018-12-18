//
// Created by Nico Wittig on 2018-12-13.
//

#include "light_element.h"

light_element::light_element(uint16_t first_led, uint16_t num_leds) {
    this->leds = (CHSV *) malloc(sizeof(CHSV) * num_leds);
    this->first_led = first_led;
    this->num_leds = num_leds;
    this->brightness = 1.0;
}

uint16_t light_element::get_first_led() const {
    return first_led;
}

uint16_t light_element::get_num_leds() const {
    return num_leds;
}

void light_element::set_brightness(float brightness) {
    light_element::brightness = brightness;
}

void light_element::show(CRGB* leds_crgb, float BRIGHTNESS) {
    for (int i = 0; i < num_leds; i++) {
        leds_crgb[first_led + i] = CHSV(leds[i].hue, leds[i].sat, static_cast<uint8_t>(leds[i].val * brightness * BRIGHTNESS));
    }

    FastLED.show();
}
