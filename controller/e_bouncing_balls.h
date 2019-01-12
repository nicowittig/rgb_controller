//
// Created by Nico Wittig on 2018-12-18.
//

#ifndef CONTROLLER_E_BOUNCING_BALLS_H
#define CONTROLLER_E_BOUNCING_BALLS_H

#include "arduino_std_definitions.h"
#include "effect.h"

/// Bouncing Balls effect which is a sub class of 'effect' and lets a defined number of colorized balls bounce in the lamp.
class e_bouncing_balls : public effect {

private:
    uint8_t ball_count;    ///< number of balls
    CHSV* colors;          ///< array of colors to colorize the balls. (must be at least as large as the ball count)

    float Gravity = -9.81; ///< gravity of the balls
    int StartHeight = 1;   ///< height of the "ground"

    float* Height;         ///< contains the height of every ball
    float ImpactVelocityStart;
    float* ImpactVelocity;
    float* TimeSinceLastBounce;
    uint32_t* ClockTimeSinceLastBounce;
    uint16_t* Position;
    float* Dampening;

public:

    /// Constructor (CHSV) - defines parameters
    /// \param le - light element to apply the effect to
    /// \param ball_count - number of balls
    /// \param colors - CHSV-color array of the balls
    e_bouncing_balls(light_element* le, uint8_t ball_count, CHSV* colors);

    /// Constructor (CRGB) - defines parameters
    /// \param le - light element to apply the effect to
    /// \param ball_count - number of balls
    /// \param colors - CRGB-color array of the balls
    e_bouncing_balls(light_element* le, uint8_t ball_count, CRGB* colors);

    /// Destructor
    virtual ~e_bouncing_balls();

    /// init is called once the effect is constructed to allocate the array etc.
    /// \return true
    virtual bool init();
    /// run is called in every iteration the effect has to continue.
    /// \return false
    virtual bool run();

};


#endif //CONTROLLER_E_BOUNCING_BALLS_H
