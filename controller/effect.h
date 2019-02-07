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
    uint8_t effect_index = 0; ///< effect index is used by various effects to safe a state or a position

protected:
    light_element* le; ///< light element the effects are applied to
    char* name;

    /// Checks the attached light element if the colors are similar to the CHSV-color array
    /// \param color - CHSV-color array
    /// \return true if the colors do match, else false
    bool check_color_matching(CHSV* color);

    // region color setter

    /// method to set a certain pixel to a specific color
    /// \param pixel
    /// \param red
    /// \param green
    /// \param blue
    void set_pixel(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
        this->le->leds[pixel] = rgb2hsv_approximate(CRGB(red, green, blue));
    }

    /// method to set a certain pixel to a specific color
    /// \param pixel - pixel index
    /// \param color - CHSV-color
    void set_pixel(uint16_t pixel, CHSV color) { this->le->leds[pixel] = color; }

    /// method to set a certain pixel to a specific color
    /// \param pixel - pixel index
    /// \param color - CRGB-color
    void set_pixel(uint16_t pixel, CRGB color) { this->le->leds[pixel] = rgb2hsv_approximate(color); }

    /// method to set all pixels of the attached light element to a specific color
    /// \param red
    /// \param green
    /// \param blue
    void set_all(uint8_t red, uint8_t green, uint8_t blue) {
        for (int i = 0; i < le->get_num_leds(); i++) le->leds[i] = rgb2hsv_approximate(CRGB(red, green, blue));
    }

    /// method to set all pixels of the attached light element to a specific color
    /// \param color - CHSV-color
    void set_all(CHSV color) { for (int i = 0; i < le->get_num_leds(); i++) le->leds[i] = color; }

    /// method to set all pixels of the attached light element to a specific color
    /// \param color - CRGB-color
    void set_all(CRGB color) { for (int i = 0; i < le->get_num_leds(); i++) le->leds[i] = rgb2hsv_approximate(color); }

    // endregion

    /// method to shift all pixels of the attached light element by the given direction-value
    /// \param direction - direction and steps to shift
    void shift(int16_t direction);

    /// method to shift only the hue-values of all pixels of the attached light element by the given direction-value
    /// This is useful if the brightness or the saturation of a pixel (field) must be fix.
    /// \param direction - direction and steps to shift
    void shift_hue(int16_t direction);

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
    effect(light_element* le, char* name) {
        this->le = le;
        this->name = name;
    }

    /// Getter for the effect name
    /// \return the name of the effect
    char* getName() { return this->name; }

    /// Destructor
    virtual ~effect() {}

    /// init is called once the effect is constructed and passes the call down to the sub class.
    /// \return the value of the sub class
    virtual bool init() = 0;

    /// run is called in every iteration the effect has to continue and passes the call down to the sub class.
    /// \return the value of the sub class
    virtual bool run() = 0;

};


#endif //CONTROLLER_EFFECT_H
