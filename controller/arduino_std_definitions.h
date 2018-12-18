//
// Created by Nico Wittig on 2018-12-14.
//

#ifndef CONTROLLER_STD_DEFINITIONS_H
#define CONTROLLER_STD_DEFINITIONS_H

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "nw_toolkit.h"

#include "lib/FastLED-3.2.0/FastLED.h"
#include <FastLED.h>

#include "lib/Adafruit_NeoPixel/Adafruit_NeoPixel.h"
#include <Adafruit_NeoPixel.h>

#define DELAY(delay) (delay_counter % ((int) ((delay) / delay_balance)) == 0 && delay_counter >= ((delay) / delay_balance))

#endif //CONTROLLER_STD_DEFINITIONS_H
