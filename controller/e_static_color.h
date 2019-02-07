//
// Created by Nico Wittig on 2019-02-07.
//

#ifndef CONTROLLER_E_STATIC_COLOR_H
#define CONTROLLER_E_STATIC_COLOR_H

#include "arduino_std_definitions.h"
#include "effect.h"

#define EFFECT_NAME "static color"

class e_static_color : public effect {

private:
    CHSV color;

public:

    /// Constructor - defines parameters
    /// \param le - light element to apply the effect to
    /// \param color - color of the element
    e_static_color(light_element* le, CHSV color);

    /// Constructor - defines parameters
    /// \param le - light element to apply the effect to
    /// \param color - color of the element
    e_static_color(light_element* le, CRGB color);

    /// Destructor
    virtual ~e_static_color();

    /// init is called once the effect is constructed to make the element a rainbow.
    /// \return true
    virtual bool init();

    /// run is called in every iteration the effect has to continue and shifts the colors.
    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_E_STATIC_COLOR_H
