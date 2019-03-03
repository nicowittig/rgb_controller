//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_INPUT_DIGITAL_H
#define CONTROLLER_INPUT_DIGITAL_H

#include "input.hpp"

/// digital input extends input
class input_digital : public input {

private:
    bool pullup; ///< adds the ability to use a digital pin with builtin pullup resistor

public:

    /// Constructor
    /// \param input_pin - Arduino pin
    /// \param pullup - use pin as with pullup resistor
    /// \param invert - inverts the input
    input_digital(uint8_t input_pin, bool pullup, bool invert);

    /// read the input and casts it to a bool
    /// \return a bool
    virtual bool digital_read();

    /// prints information of the input to the Arduino's serial
    virtual void print_to_serial();

};


#endif //CONTROLLER_INPUT_DIGITAL_H
