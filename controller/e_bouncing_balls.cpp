//
// Created by Nico Wittig on 2018-12-18.
//

#include "e_bouncing_balls.h"

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CHSV* colors) : effect(le) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (int i = 0; i < ball_count; i++) this->colors[i] = colors[i];
}

e_bouncing_balls::e_bouncing_balls(light_element *le, uint8_t ball_count, CRGB *colors, CRGB* crgb_leds) : effect(le) {
    this->ball_count = ball_count;
    this->colors = (CHSV *) malloc(sizeof(CHSV) * ball_count);
    for (int i = 0; i < ball_count; i++) this->colors[i] = rgb2hsv_approximate(colors[i]);

    this->crgb_leds = crgb_leds;
}

e_bouncing_balls::~e_bouncing_balls() {

}

bool e_bouncing_balls::init() {
    Serial.println("init: e_bouncing_balls");

    set_all(CRGB::Black);
    return false;
}

bool e_bouncing_balls::run() {
    Serial.println("run: e_bouncing_balls");

    float Gravity = -9.81;
    int StartHeight = 1;

    float Height[ball_count];
    float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
    float ImpactVelocity[ball_count];
    float TimeSinceLastBounce[ball_count];
    int   Position[ball_count];
    long  ClockTimeSinceLastBounce[ball_count];
    float Dampening[ball_count];

    for (int i = 0 ; i < ball_count ; i++) {
        ClockTimeSinceLastBounce[i] = millis();
        Height[i] = StartHeight;
        Position[i] = 0;
        ImpactVelocity[i] = ImpactVelocityStart;
        TimeSinceLastBounce[i] = 0;
        Dampening[i] = 0.90 - float(i)/pow(ball_count,2);
    }

    while (true) {
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
        }


        for (int i = 0; i < ball_count; i++) {
            set_pixel(Position[i], colors[i]);
        }

        le->show(this->crgb_leds, 1);
        set_all(CRGB::Black);

    }

    //setAll(0,0,0);



    return false;
}
