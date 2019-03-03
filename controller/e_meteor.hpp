//
// Created by Nico Wittig on 2019-03-03.
//

#ifndef CONTROLLER_E_METEOR_H
#define CONTROLLER_E_METEOR_H

#include "arduino_std_definitions.h"
#include "effect.hpp"

#define EFFECT_NAME "meteor"

class e_meteor : public effect {

private:
    bool forward; ///< let the meteor fly forward or backward
    uint8_t trail_decay; ///< value to decrease the trail brightness randomly
    uint16_t meteor_position = 0; ///< current position of the meteor

public:

    // Constructor
    e_meteor(light_element* le, bool forward, uint8_t trail_decay);

    /// Destructor
    ~e_meteor();

    /// init is called once the effect is constructed to colorize the element
    /// \return true
    virtual bool init();

    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_E_METEOR_H
