//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_LIGHT_ELEMENT_H
#define CONTROLLER_LIGHT_ELEMENT_H

#include "arduino_std_definitions.h"

class light_element {
private:
    uint16_t first_led;
    uint16_t num_leds;
    float brightness;

public:
    light_element(uint16_t first_led, uint16_t num_leds);

    CHSV* leds;

    uint16_t get_first_led() const;
    uint16_t get_num_leds() const;
    void set_brightness(float brightness);

    void set_all(CRGB color);
    void show(CRGB* leds_crgb, float BRIGHTNESS);
};


#endif //CONTROLLER_LIGHT_ELEMENT_H
