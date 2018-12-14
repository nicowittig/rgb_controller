//
// Created by Nico Wittig on 2018-12-13.
//

#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "arduino_std_definitions.h"

#include "effect.h"
//#include "input.h"
#include "light_element.h"

#include "e_fire.h"

void c_setup();
void c_loop();

void adjust_sensors();
void refresh_inputs();
void show_all_pixels();

#endif //CONTROLLER_CONTROLLER_H
