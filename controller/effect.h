//
// Created by Nico Wittig on 2018-12-14.
//

#ifndef CONTROLLER_EFFECT_H
#define CONTROLLER_EFFECT_H

#include "arduino_std_definitions.h"
#include "light_element.h"

class effect {

private:
    uint8_t effect_index;

protected:
    light_element* le;

    bool check_color_matching(CHSV* color);
    bool fade_manual(uint8_t* var, uint8_t end, int8_t step);

    void set_pixel(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void shift(int16_t direction);
    void shift_hue(int16_t direction);
    bool wipe(CHSV new_color, int8_t direction);
    bool fade(CHSV new_color, int8_t step);

public:
    effect(light_element* le);
    virtual ~effect();

    virtual bool init() = 0;
    virtual bool run() = 0;

};


#endif //CONTROLLER_EFFECT_H
