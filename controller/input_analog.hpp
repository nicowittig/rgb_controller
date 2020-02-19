//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_INPUT_ANALOG_H
#define CONTROLLER_INPUT_ANALOG_H

#include "input.hpp"

/// analog input extends input
class input_analog : public input {

private:
    uint16_t trigger_value; ///< the boarder value to decide whether the input is "on" or "off" in a digital meaning
    uint16_t trigger_adjustment_duration; ///< parameter to define the record time for the automatic calculation of the trigger value
    float trigger_adjustment_tolerance; ///< parameter to define the tolerance for the automatic calculation of the trigger value


public:

    /// Constructor
    /// \param input_pin - Arduino pin
    /// \param trigger_value - the boarder value to decide whether the input is "on" or "off" in a digital meaning
    /// \param invert - inverts the input
    input_analog(uint8_t input_pin, uint16_t trigger_value, bool invert);

    /// Constructor
    /// \param input_pin - Arduino pin
    /// \param trigger_adjustment_duration - parameter to define the record time for the automatic calculation of the trigger value
    /// \param trigger_adjustment_tolerance - parameter to define the tolerance for the automatic calculation of the trigger value
    /// \param invert - inverts the input
    input_analog(uint8_t input_pin, uint16_t trigger_adjustment_duration, float trigger_adjustment_tolerance, bool invert);

    /// Constructor
    /// trigger value is 1
    /// \param input_pin - Arduino pin
    /// \param invert - inverts the input
    input_analog(uint8_t input_pin, bool invert);

    /// set the trigger values
    /// \param trigger_value - the boarder value to decide whether the input is "on" or "off" in a digital meaning
    void set_trigger_value(uint16_t trigger_value);

    /// set the duration and the tolerance for the automatic calculation of the trigger value
    /// \param duration - parameter to define the record time for the automatic calculation of the trigger value
    /// \param tolerance - parameter to define the tolerance for the automatic calculation of the trigger value
    void set_trigger_adjustment_values(uint16_t duration, float tolerance);

    /// automatic calculation of the trigger value with given parameters
    /// \param duration - parameter to define the record time for the automatic calculation of the trigger value
    /// \param tolerance - parameter to define the tolerance for the automatic calculation of the trigger value
    void adjust_trigger_value(uint16_t duration, float tolerance);

    /// automatic calculation of the trigger value with the local parameters
    void adjust_trigger_value();

    /// get the raw analog value of the input's pin
    /// \return the analog value of the current on the input's pin
    uint16_t analog_read();

    /// read the input and casts it to a bool
    /// \return a bool
    virtual bool digital_read();

    /// prints information of the input to the Arduino's serial
    virtual void print_to_serial();

};


#endif //CONTROLLER_INPUT_ANALOG_H
