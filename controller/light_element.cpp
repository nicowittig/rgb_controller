//
// Created by Nico Wittig on 2018-12-13.
//

#include "light_element.hpp"

light_element::light_element(uint16_t first_led, uint16_t num_leds) {
    this->leds = (CHSV *) malloc(sizeof(CHSV) * num_leds);
    this->first_led = first_led;
    this->num_leds = num_leds;
    this->brightness = 1.0;
}

//region Getter & Setter

uint16_t light_element::get_first_led() const {
    return first_led;
}

uint16_t light_element::get_num_leds() const {
    return num_leds;
}

void light_element::set_brightness(float brightness) {
    light_element::brightness = brightness;
}

//endregion

void light_element::set_all(CHSV color) {
    for (uint16_t led = 0; led < num_leds; led++) {
        leds[led] = color;
    }
}

void light_element::set_all(CRGB color) {
    for (uint16_t led = 0; led < num_leds; led++) {
        leds[led] = rgb2hsv_approximate(color);
    }
}

void light_element::show(CRGB* leds_crgb, float BRIGHTNESS) {
    for (uint16_t led = 0; led < num_leds; led++) {
        leds_crgb[first_led + led] = CHSV(leds[led].hue, leds[led].sat, static_cast<uint8_t>(leds[led].val * brightness * BRIGHTNESS));
    }

    FastLED.show();
}
