//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "arduino_std_definitions.h"
#include "light_element.h"
//#include "input.h"
#include "effect_inclusions.h"

#define delay_balance 36
#define LED_PIN 6
#define NUM_LEDS 77
#define num_elements 1

/// Controller class to initialize inputs and outputs, pull the inputs, launch effects and show the result.
class controller {
private:
    uint16_t delay_counter = 0; // TODO switch from counter to millis()

    uint8_t cur_mode; ///< current effect mode
    uint8_t new_mode; ///< next effect mode

    float brightness = 1; ///< brightness of the strip (between 0 and 1)

    CRGB crgb_leds[NUM_LEDS]; ///< RGB array of all the pixels
    light_element* l_elements = (light_element *) malloc(sizeof(light_element) * num_elements); ///< sub-elements of the strip
    effect* effects [num_elements]; ///< one effect for every element

    /// Adjust all IR-sensors to the current light intensity of the surrounding.
    void adjust_sensors() {
        //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].adjust_trigger_value();
        //Serial.println("[Sensor-Reset]");
    }
    /// Let the input-classes check if there was an input.
    void refresh_inputs() {
        //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].refresh_state();
        //microphone[0].refresh_state();
    }
    /// Show all sub-elements and call the FastLED output.
    void show_all_pixels() {
        for (int i = 0; i < num_elements; i++) l_elements[i].show(crgb_leds, brightness);
        FastLED.show();
    }

public:
    /// Constructor
    controller(){}

    /// The setup method is triggered once by the controller.ino when the Arduino starts.
    void setup();
    /// The loop method is triggered by the controller.ino from the Arduino.
    void loop();

    /// Get the currently active mode.
    /// \return the current mode as integer
    uint8_t get_mode() const { return cur_mode; }

    /// Switch the strip to a new mode.
    /// \param mode - new mode
    void set_mode(uint8_t mode) { new_mode = mode; }

    /// Get the brightness of the whole strip. The result should be between 0 and 1.
    /// \return brithness of the strip
    float getBrightness() const { return brightness; }

    /// Set the brightness of the whole strip to a value between 0 and 1.
    /// \param brightness - the brightness of the whole strip
    /// \return true if the brightness is between 0 and 1, else false
    bool setBrightness(float brightness) {
        if (brightness < 0 || brightness > 1) return false;
        this->brightness = brightness;
        return true;
    }

};

#endif //CONTROLLER_CONTROLLER_H
