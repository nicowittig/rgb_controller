//
// Created by Nico Wittig on 2018-12-19.
//

#ifndef CONTROLLER_E_RAINBOW_SHIFT_H
#define CONTROLLER_E_RAINBOW_SHIFT_H

#include "arduino_std_definitions.h"
#include "effect.h"

#define EFFECT_NAME "rainbow shift"

/// Rainbow effect which is a sub class of 'effect' and makes the light element a rainbow and slowly shifts the colors.
class e_rainbow_shift : public effect {

public:

    /// Constructor - defines parameters
    /// \param le - light element to apply the effect to
    e_rainbow_shift(light_element* le);

    /// Destructor
    virtual ~e_rainbow_shift();

    /// init is called once the effect is constructed to make the element a rainbow.
    /// \return true
    virtual bool init();

    /// run is called in every iteration the effect has to continue and shifts the colors.
    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_E_RAINBOW_SHIFT_H
