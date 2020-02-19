//
// Created by Nico Wittig on 2018-12-13.
//

#include "input.hpp"


input::input(uint8_t input_pin, bool invert) {
    this->input_pin = input_pin;
    this->invert = invert;

    // initialize standard arrays
    for (int i = 0; i < 4; i++) {
        state[i] = false;
        ready_for_next_input[i] = true;
    }
}


bool input::digital_read() {
}


void input::refresh_state() {

    // Push Mode
    state[0] = digital_read();

    // Toggle Mode
    if (digital_read()) {
        if (ready_for_next_input[1]) {
            ready_for_next_input[1] = false;
            state[1] = !state[1];
        }
    } else {
        ready_for_next_input[1] = true;
    }

    // Tap Mode
    if (digital_read()) {
        if (ready_for_next_input[2]) {
            ready_for_next_input[2] = false;
            state[2] = true;
        }
    } else {
        ready_for_next_input[2] = true;
        state[2] = false;
    }

    // Change Mode
    if (!state[3]) {
        if (ready_for_next_input[3] != digital_read()) {
            ready_for_next_input[3] = digital_read();
            state[3] = true;
        }
    }

}


bool input::is_pushed() {
    return state[0];
}


bool input::is_toggled() {
    return state[1];
}


bool input::is_tapped() {
    if (state[2]) {
        state[2] = false;
        return true;
    } else {
        return false;
    }
}


bool input::is_changed() {
    if (state[3]) {
        state[3] = false;
        return true;
    } else {
        return false;
    }
}


void input::print_to_serial() {
    Serial.println(digital_read());
}