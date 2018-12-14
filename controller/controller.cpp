//
// Created by Nico Wittig on 2018-12-13.
//

#include "controller.h"

#define delay_balance 36
#define BRIGHTNESS 1

#define LED_PIN 6

#define NUM_LEDS 166
#define num_elements 1

CRGB crgb_leds[NUM_LEDS];
light_element* l_elements;
effect* effects;

void c_setup() {
    FastLED.addLeds<WS2812, LED_PIN, GRB>(crgb_leds, NUM_LEDS);
    for (uint16_t i = 0; i < NUM_LEDS; i++) crgb_leds[i] = CRGB::Black;

    l_elements = (light_element *) malloc(sizeof(light_element) * num_elements);
    effects = (effect *) malloc(sizeof(effect) * num_elements);

    l_elements[0] = light_element(0, 15);
    effects[0];

    show_all_lights();
}

short int i = 0;
uint8_t mode = -1;

void c_loop() {
    if (Serial.available() > 0) {
        char message = Serial.read();

        Serial.print("Received message: ");
        Serial.println(message);

        switch(message) {
            case 'r': c_setup(); mode = -1;
                break;
            default: break;
        }

        if ((message - 48) >= 0 && (message - 48) <= 9) {
            mode = (message - 48);
        }
    }



    switch(mode) {
        case 0 : fade(); delay(500); break;
        case 1 : shift(); delay(50); break;
        case 2 : Fire(55,120,15); break;
        case 3 : {
            uint8_t colors[3][3] = { {0xff, 0,0},
                                  {0, 0xff, 0},
                                  {0, 0, 0xff} };

            BouncingColoredBalls(3, colors);
            break;
        }
        case 4 : Twinkle(0xff, 0, 0, 10, 100, false); break;
        case 5 : Sparkle(random(255), 255, 50); break;
        default: break;
    }
}

void adjust_sensors() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].adjust_trigger_value();
    //Serial.println("[Sensor-Reset]");
}

void refresh_inputs() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].refresh_state();
    //microphone[0].refresh_state();
}

void show_all_lights() {
    for (int i = 0; i < num_elements; i++) l_elements[i].show(crgb_leds, BRIGHTNESS);
    //FastLED.show();
}