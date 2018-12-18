//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "arduino_std_definitions.h"
#include "light_element.h"
//#include "input.h"
#include "effect_inclusions.h"

#define delay_balance 36
#define LED_PIN 6
#define NUM_LEDS 15 //77
#define num_elements 1

class controller {
private:
    uint16_t delay_counter = 0;

    uint8_t cur_mode;
    uint8_t new_mode;

    float brightness = 1;

    CRGB crgb_leds[NUM_LEDS];
    light_element* l_elements = (light_element *) malloc(sizeof(light_element) * num_elements);
    effect* effects [num_elements];

    void adjust_sensors();
    void refresh_inputs();
    void show_all_pixels();

public:
    //controller();

    void setup();
    void loop();

    uint8_t get_mode() const;
    void set_mode(uint8_t mode);
    float getBrightness() const;
    bool setBrightness(float brightness);
};

#endif //CONTROLLER_CONTROLLER_H
