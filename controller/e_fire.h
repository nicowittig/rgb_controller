//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_FIRE_H
#define CONTROLLER_FIRE_H

#include "arduino_std_definitions.h"
#include "effect.h"


class e_fire : public effect {

private:
    int16_t cooling;
    int16_t sparking;
    void set_pixel_heat_color(uint16_t pixel, uint8_t temperature);

public:
    e_fire(light_element le, int16_t cooling, int16_t sparking);
    virtual bool init();
    virtual bool run();

};


#endif //CONTROLLER_FIRE_H
