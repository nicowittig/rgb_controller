//
// Created by Nico Wittig on 2018-12-14.
//

#ifndef CONTROLLER_EFFECT_H
#define CONTROLLER_EFFECT_H

#include "arduino_std_definitions.h"
#include "light_element.h"

/// Super class of all the effects, which provides the effects with standard functionality.
class effect {

private:
    uint8_t wipe_index = 0; ///< effect index is used by various effects to safe a state or a position

protected:
    light_element* le; ///< light element the effects are applied to
    char* name; // TODO use case for name

    /// Checks the attached light element if the colors are similar to the CHSV-color array
    /// \param color - CHSV-color array
    /// \return true if the colors do match, else false
    bool check_color_matching(CHSV* color);

// region color setter

    /// method to set a certain pixel to a specific color
    /// \param pixel - pixel index
    /// \param color - CHSV-color
    void set_pixel(uint16_t pixel, CHSV color);

    /// method to set a certain pixel to a specific color
    /// \param pixel - pixel index
    /// \param color - CRGB-color
    void set_pixel(uint16_t pixel, CRGB color);

    /// set one or multiple gradients from the first to the second color in specified area on the light element
    /// \param begin_color - first color
    /// \param end_color - second color
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    /// \param begin_led - first led of the area
    /// \param end_led - second led of the area
    /// \param cycles - multiple gradient cycles
    /// \param forward_only - if true invert every 2nd gradient
    void set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led, uint8_t cycles, bool forward_only);

    /// set one or multiple gradients from the first to the second color in specified area on the light element
    /// \param begin_color - first color
    /// \param end_color - second color
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    /// \param begin_led - first led of the area
    /// \param end_led - second led of the area
    /// \param cycles - multiple gradient cycles
    void set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led, uint8_t cycles);

    /// set a gradient from the first to the second color in specified area on the light element
    /// \param begin_color - first color
    /// \param end_color - second color
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    /// \param begin_led - first led of the area
    /// \param end_led - second led of the area
    void set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward, uint16_t begin_led, uint16_t end_led);

    /// set a gradient from the first to the second color to the whole light element
    /// \param begin_color - first color
    /// \param end_color - second color
    /// \param hue_cycle_forward - direction to walk through the hue colors
    //    /// true: red, yellow, green, blue, red
    //    /// false: red, blue, green, yellow, red
    void set_color(CHSV begin_color, CHSV end_color, bool hue_cycle_forward);

    /// set a gradient from the first to the second color to the whole light element
    /// \param begin_color - first color
    /// \param end_color - second color
    void set_color(CHSV begin_color, CHSV end_color);

    /// set the whole light element to the given color
    /// \param color - Color
    void set_color(CHSV color);

// endregion

    /// method to increase the hue of every pixel of the attached light element by value
    /// \param value  - value to increase the hue
    void increase_hue(int16_t value);

    /// method to shift all pixels of the attached light element by the given direction-value
    /// \param direction - direction and steps to shift
    void shift(int16_t direction);

    /// method to shift only the hue-values of all pixels of the attached light element by the given direction-value
    /// This is useful if the brightness or the saturation of a pixel (field) must be fix.
    /// \param direction - direction and steps to shift
    void shift_hue(int16_t direction);

    // TODO make method without wipe_helper
    /// method to wipe a color through the light element
    /// \param new_color - CHSV-color
    /// \param direction - direction to wipe
    /// \return true if the wipe is complete, else false
    bool wipe(CHSV new_color, int8_t direction);

    /// method to fade one single parameter to a certain value by the given steps
    /// \param var - pointer to the parameter that has to be changed
    /// \param end - goal value
    /// \param step - steps
    /// \return true if the goal value is reached, else false
    bool fade_manual(uint8_t* var, uint8_t end, int8_t step);

    /// method to fade all pixels of the attached light element to a certain CHSV-color
    /// \param new_color - goal color to be faded to
    /// \param step - steps
    /// \return true if the goal color is reached, else false
    bool fade(CHSV new_color, int8_t step);

public:

    /// Constructor
    /// \param le - light element the effects are applied to
    effect(light_element* le, char* name);

    /// Destructor
    virtual ~effect();

    /// Getter for the effect name
    /// \return the name of the effect
    char* getName();

    /// init is called once the effect is constructed and passes the call down to the sub class.
    /// \return the value of the sub class
    virtual bool init() = 0;

    /// run is called in every iteration the effect has to continue and passes the call down to the sub class.
    /// \return the value of the sub class
    virtual bool run() = 0;

};


#endif //CONTROLLER_EFFECT_H
