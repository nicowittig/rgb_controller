//
// Created by Nico Wittig on 2018-12-18.
//

#ifndef CONTROLLER_E_BOUNCING_BALLS_H
#define CONTROLLER_E_BOUNCING_BALLS_H

#include "arduino_std_definitions.h"
#include "effect.h"

class e_bouncing_balls : public effect {

private:
    uint8_t ball_count;
    CHSV* colors;
    CRGB* crgb_leds;

public:
    e_bouncing_balls(light_element* le, uint8_t ball_count, CHSV* colors);
    e_bouncing_balls(light_element* le, uint8_t ball_count, CRGB* colors, CRGB* crgb_leds);
    virtual ~e_bouncing_balls();
    virtual bool init();
    virtual bool run();

};


#endif //CONTROLLER_E_BOUNCING_BALLS_H
