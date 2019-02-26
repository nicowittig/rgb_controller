//
// Created by Nico Wittig on 2018-12-18.
//

#include "e_bouncing_balls.h"

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CHSV* colors) : effect(le, EFFECT_NAME) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (int ball = 0; ball < ball_count; ball++) this->colors[ball] = colors[ball];
}

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CRGB *colors) : effect(le, EFFECT_NAME) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (uint8_t ball = 0; ball < ball_count; ball++) this->colors[ball] = rgb2hsv_approximate(colors[ball]);
}

e_bouncing_balls::~e_bouncing_balls() {
    free(colors);

    free(Height);
    free(ImpactVelocity);
    free(TimeSinceLastBounce);
    free(Position);
    free(ClockTimeSinceLastBounce);
    free(Dampening);
}

bool e_bouncing_balls::init() {

    ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );

    Height = (float *) malloc(sizeof(float) * ball_count);
    ImpactVelocity = (float *) malloc(sizeof(float) * ball_count);
    TimeSinceLastBounce = (float *) malloc(sizeof(float) * ball_count);
    Position = (uint16_t *) malloc(sizeof(uint16_t) * ball_count);
    ClockTimeSinceLastBounce = (uint32_t *) malloc(sizeof(uint32_t) * ball_count);
    Dampening = (float *) malloc(sizeof(float) * ball_count);

    for (int ball = 0 ; ball < ball_count ; ball++) {
        ClockTimeSinceLastBounce[ball] = millis();
        Height[ball] = StartHeight;
        Position[ball] = 0;
        ImpactVelocity[ball] = ImpactVelocityStart;
        TimeSinceLastBounce[ball] = 0;
        Dampening[ball] = 0.90 - float(ball)/pow(ball_count,2);
    }

    set_all(CRGB::Black);

    return true;
}

bool e_bouncing_balls::run() {

    set_all(CRGB::Black);

    for (int ball = 0; ball < ball_count; ball++) {
        TimeSinceLastBounce[ball] = millis() - ClockTimeSinceLastBounce[ball];
        Height[ball] = 0.5 * Gravity * pow(TimeSinceLastBounce[ball] / 1000, 2.0) +
                ImpactVelocity[ball] * TimeSinceLastBounce[ball] / 1000;

        if (Height[ball] < 0) {
            Height[ball] = 0;
            ImpactVelocity[ball] = Dampening[ball] * ImpactVelocity[ball];
            ClockTimeSinceLastBounce[ball] = millis();

            if (ImpactVelocity[ball] < 0.01) {
                ImpactVelocity[ball] = ImpactVelocityStart;
            }
        }
        Position[ball] = round(Height[ball] * (le->get_num_leds() - 1) / StartHeight);

        set_pixel(Position[ball], colors[ball]);
    }

    return false;
}
