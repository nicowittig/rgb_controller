//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_FIRE_H
#define CONTROLLER_FIRE_H

#include "arduino_std_definitions.h"
#include "effect.h"

#define EFFECT_NAME "fire"

/// Fire effect which is a sub class of 'effect' and randomly lights up a fire simulation along a light element.
class e_fire : public effect {

private:
    int16_t cooling; ///< cooling parameter of the fire
    int16_t sparking; ///< sparking parameter of the fire

    /// lights a specific pixel to a color, which represents a certain temperature.
    /// \param pixel - pixel to be colored
    /// \param temperature ///< temperature of the pixel (0-255)
    void set_pixel_heat_color(uint16_t pixel, uint8_t temperature);

public:

    /// Constructor - defines parameters
    /// \param le - light element to apply the effect to
    /// \param cooling - cooling parameter of the fire
    /// \param sparking - sparking parameter of the fire
    e_fire(light_element* le, int16_t cooling, int16_t sparking);

    /// Destructor
    virtual ~e_fire();

    /// init is called once the effect is constructed to darken (reset) the fire.
    /// \return true
    virtual bool init();

    /// run is called in every iteration the effect has to continue.
    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_FIRE_H
