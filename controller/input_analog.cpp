//
// Created by Nico Wittig on 2018-12-13.
//

#include "input_analog.hpp"

//region Constructors and Setters

input_analog::input_analog(uint8_t input_pin, uint16_t trigger_value, bool invert) : input(input_pin, invert) {
    this->trigger_value = trigger_value;
}


input_analog::input_analog(uint8_t input_pin, uint16_t trigger_adjustment_duration, float trigger_adjustment_tolerance,
                           bool invert) : input(input_pin, invert) {
    set_trigger_adjustment_values(trigger_adjustment_duration, trigger_adjustment_tolerance);
    adjust_trigger_value();
}


input_analog::input_analog(uint8_t input_pin, bool invert) : input(input_pin, invert) {
    this->trigger_value = 1;
}


void input_analog::set_trigger_value(uint16_t trigger_value) {
    this->trigger_value = trigger_value;
}


void input_analog::set_trigger_adjustment_values(uint16_t duration, float tolerance) {
    this->trigger_adjustment_duration = duration;
    this->trigger_adjustment_tolerance = tolerance;
}

//endregion

void input_analog::adjust_trigger_value(uint16_t duration, float tolerance) {
    set_trigger_adjustment_values(duration, tolerance);
    adjust_trigger_value();
}


void input_analog::adjust_trigger_value() {
    uint16_t min_value = 0u-1;

    // get the min value from a specific "recording range"
    for (int i = 0; i < trigger_adjustment_duration; i++) {
        uint16_t val = analog_read();
        if (val < min_value) min_value = val;
    }

    // set the new trigger value with consideration of the tolerance
    set_trigger_value(static_cast<uint16_t>(min_value * (1-trigger_adjustment_tolerance)));
}


uint16_t input_analog::analog_read() {
    return analogRead(input_pin);
}


bool input_analog::digital_read() {
    return (analog_read() >= trigger_value) != invert;
}


void input_analog::print_to_serial() {
    Serial.print(analog_read());
    Serial.print(" trigger: ");
    Serial.print(trigger_value);
    Serial.println();
}
