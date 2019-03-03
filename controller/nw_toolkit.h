//
// Created by Nico Wittig on 2018-12-14.
//

#ifndef CONTROLLER_NW_TOOLKIT_H
#define CONTROLLER_NW_TOOLKIT_H

/// Calculates a%b with a positive result, so -1%3 will be 2 and not -1.
/// \param a - first parameter
/// \param b - second parameter
/// \return the modulo value of a%b
int modulo(int a, int b);

/// Get the free RAM of the Arduino.
/// \return the free RAM
int freeRam();

/// reset the Arduino
void soft_reset();

#endif //CONTROLLER_NW_TOOLKIT_H
