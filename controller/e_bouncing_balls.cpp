//
// Created by Nico Wittig on 2018-12-18.
//

#include "e_bouncing_balls.h"

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CHSV* colors) : effect(le, EFFECT_NAME) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (int i = 0; i < ball_count; i++) this->colors[i] = colors[i];
}

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CRGB *colors) : effect(le, EFFECT_NAME) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (uint8_t i = 0; i < ball_count; i++) this->colors[i] = rgb2hsv_approximate(colors[i]);
}

e_bouncing_balls::~e_bouncing_balls() {
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

    for (int i = 0 ; i < ball_count ; i++) {
        ClockTimeSinceLastBounce[i] = millis();
        Height[i] = StartHeight;
        Position[i] = 0;
        ImpactVelocity[i] = ImpactVelocityStart;
        TimeSinceLastBounce[i] = 0;
        Dampening[i] = 0.90 - float(i)/pow(ball_count,2);
    }

    set_all(CRGB::Black);

    return true;
}

bool e_bouncing_balls::run() {

    set_all(CRGB::Black);

    for (int i = 0; i < ball_count; i++) {
        TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
        Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) +
                ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

        if (Height[i] < 0) {
            Height[i] = 0;
            ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
            ClockTimeSinceLastBounce[i] = millis();

            if (ImpactVelocity[i] < 0.01) {
                ImpactVelocity[i] = ImpactVelocityStart;
            }
        }
        Position[i] = round(Height[i] * (le->get_num_leds() - 1) / StartHeight);

        set_pixel(Position[i], colors[i]);
    }

    return false;
}
