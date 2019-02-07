//
// Created by Nico Wittig on 2018-12-13.
//

#include "e_fire.h"

e_fire::e_fire(light_element* le, int16_t cooling, int16_t sparking) : effect(le, EFFECT_NAME) {
    this->cooling = cooling;
    this->sparking = sparking;
}

e_fire::~e_fire() {

}

bool e_fire::init() {
    le->set_all(CRGB::Black);
    return true;
}

bool e_fire::run() {

    uint8_t* heat = (uint8_t *) malloc(sizeof(uint8_t) * le->get_num_leds());
    int cooldown;

    // Step 1.  Cool down every cell a little
    for(uint16_t i = 0; i < le->get_num_leds(); i++) {

        cooldown = random(0, ((cooling * 10) / le->get_num_leds()) + 2);

        if(cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i]-cooldown;
        }

    }



    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for(uint16_t k = le->get_num_leds() - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if(random(255) < sparking) {
        uint8_t y = random(7);
        heat[y] = heat[y] + random(160,255);
        //heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for(uint16_t j = 0; j < le->get_num_leds(); j++) {
        set_pixel_heat_color(j, heat[j] );
    }


    free(heat);

    return false;
}

void e_fire::set_pixel_heat_color(uint16_t pixel, uint8_t temperature) {
    // Scale 'heat' down from 0-255 to 0-191
    uint8_t t192 = round((temperature/255.0)*191);

    // calculate ramp up from
    uint8_t heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2; // scale up to 0..252

    // figure out which third of the spectrum we're in:
    if( t192 > 0x80) {                     // hottest
        set_pixel(pixel, 255, 255, heatramp);
    } else if( t192 > 0x40 ) {             // middle
        set_pixel(pixel, 255, heatramp, 0);
    } else {                               // coolest
        set_pixel(pixel, heatramp, 0, 0);
    }
}
