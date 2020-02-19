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
    bool no_random = false; ///< let the trail fade off randomly or not
    uint8_t trail_decay; ///< value to decrease the trail brightness randomly
    uint16_t meteor_position = 0; ///< current position of the meteor

public:

    /// Constructor
    /// \param le - light element
    /// \param forward - direction of the meteor
    /// \param trail_decay - trail decay
    e_meteor(light_element* le, bool forward, uint8_t trail_decay);

    /// Constructor
    /// \param le - light element
    /// \param forward - direction of the meteor
    /// \param trail_decay - trail decay
    /// \param no_random - let the trail fade off randomly or not
    e_meteor(light_element* le, bool forward, uint8_t trail_decay, bool no_random);

    /// Destructor
    ~e_meteor();

    /// init is called once the effect is constructed to colorize the element
    /// \return true
    virtual bool init();

    /// \return false
   virtual bool run();

};


#endif //CONTROLLER_E_METEOR_H
