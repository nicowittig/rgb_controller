//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_INPUT_H
#define CONTROLLER_INPUT_H

#include "arduino_std_definitions.h"

/// super class of all analog and digital inputs
class input {

    /// Button Modes:
    /// 0 - Push Mode   - 1 if the input is pressed, else false
    /// 1 - Toggle Mode - switches between 1 and 0 with every press of the input (release-unlock)
    /// 2 - Tap Mode    - 1 if the input is pressed but switches after the call to 0
    /// 3 - Change Mode - 1 if the input changes its state and switches after the call to 0

private:
    bool state[4]; ///< these are the states of the input in the different modes
    bool ready_for_next_input[4]; ///< acts like a helper for the different modes

protected:
    uint8_t input_pin; ///< Arduino pin of the input
    bool invert; ///< inverts the input

public:

    /// Constructor
    /// \param input_pin - Arduino pin
    /// \param invert - inverts the input
    input(uint8_t input_pin, bool invert);

    /// read the input and casts it to a bool
    /// \return a bool
    virtual bool digital_read();

    /// prints information of the input to the Arduino's serial
    virtual void print_to_serial();

    /// refresh all the modes to achieve the wanted modes
    void refresh_state();

    /// get the state of the Push Mode
    /// \return a bool
    bool is_pushed();
    /// get the state of the Toggle Mode
    /// \return a bool
    bool is_toggled();
    /// get the state of the Tap Mode
    /// \return a bool
    bool is_tapped();
    /// get the state of the Change Mode
    /// \return a bool
    bool is_changed();

};


#endif //CONTROLLER_INPUT_H
