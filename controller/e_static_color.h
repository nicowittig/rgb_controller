//
// Created by Nico Wittig on 2019-02-07.
//

#ifndef CONTROLLER_E_STATIC_COLOR_H
#define CONTROLLER_E_STATIC_COLOR_H

#include "arduino_std_definitions.h"
#include "effect.h"

#define EFFECT_NAME "static color"

// Colorize the element in a static color
class e_static_color : public effect {

private:
    CHSV begin_color; ///< first gradient color
    CHSV end_color; ///< second gradient color
    bool hue_cycle_forward = true; ///< direction to walk through the hue colors
                                   /// true: red, yellow, green, blue, red
                                   /// false: red, blue, green, yellow, red
    uint8_t cycles = 1; ///< number of gradients cycles
    bool forward_only = true; ///< invert every second gradient


public:

    /// Constructor - defines parameters
    /// \param le - light element to apply the effect to
    /// \param color - color of the element
    e_static_color(light_element* le, CHSV color);

    /// Constructor
    /// \param le - light element to apply the effect to
    /// \param begin_color - beginning color of the element's gradient
    /// \param end_color - ending color of the element's gradient
    e_static_color(light_element* le, CHSV begin_color, CHSV end_color);

    /// Constructor
    /// \param le - light element to apply the effect to
    /// \param begin_color - beginning color of the element's gradient
    /// \param end_color - ending color of the element's gradient
    /// \param hue_cycle_forward  - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    e_static_color(light_element* le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward);

    /// Constructor
    /// \param le - light element to apply the effect to
    /// \param begin_color - beginning color of the element's gradient
    /// \param end_color - ending color of the element's gradient
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    /// \param cycles - number of gradients in this light element
    e_static_color(light_element* le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint8_t cycles);

    /// Constructor
    /// \param le - light element to apply the effect to
    /// \param begin_color - beginning color of the element's gradient
    /// \param end_color - ending color of the element's gradient
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    /// \param cycles - number of gradients in this light element
    /// \param forward_only - if true invert every 2nd gradient
    e_static_color(light_element* le, CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint8_t cycles, bool forward_only);

    /// Destructor
    virtual ~e_static_color();

    /// init is called once the effect is constructed to colorize the element
    /// \return true
    virtual bool init();

    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_E_STATIC_COLOR_H
