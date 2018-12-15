//
// Created by Nico Wittig on 2018-12-13.
//

#include "controller.h"

#define delay_balance 36
#define BRIGHTNESS 1

#define LED_PIN 6

#define NUM_LEDS 15 //77
#define num_elements 1

CRGB crgb_leds[NUM_LEDS];
light_element* l_elements;
effect* effects [num_elements];

void c_setup() {
    Serial.begin(4800);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(crgb_leds, NUM_LEDS);
    for (uint16_t i = 0; i < NUM_LEDS; i++) crgb_leds[i] = CRGB::Black;

    l_elements = (light_element *) malloc(sizeof(light_element) * num_elements);

    l_elements[0] = light_element(0, 15);
    effects[0] = new e_fire(l_elements[0], 55, 120);


    for (int i = 0; i < l_elements[0].get_num_leds(); i++) {
        //l_elements[0].leds[i] = CHSV(i*255/15, 255, 255);
        l_elements[0].leds[i] = CHSV(0, 255, 255);
    }

    show_all_pixels();

}

uint8_t mode = 1;
uint8_t hue = 0;

void c_loop() {
    Serial.println(freeRam());
    Serial.println(hue++);




    for (int i = 0; i < l_elements[0].get_num_leds(); i++) {
        //l_elements[0].leds[i] = CHSV(hue++, 255, 255);
    }
    delay(100);


    effects[0]->run();




    if (Serial.available() > 0) {

        char message = Serial.read();

        //Serial.print("Received message: ");
        //Serial.println(message);

        switch(message) {
            case 'r': {
                c_setup();
                mode = -1;
                break;
            }

            default: break;
        }

        if ((message - 48) >= 0 && (message - 48) <= 9) {
            mode = (uint8_t) (message - 48);
        }

    }



    switch(mode) {
        case 0 : {
            //effects[0].run();
            delay(15);
            break;
        }
        default: break;
    }

    show_all_pixels();

}

void adjust_sensors() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].adjust_trigger_value();
    //Serial.println("[Sensor-Reset]");
}

void refresh_inputs() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].refresh_state();
    //microphone[0].refresh_state();
}

void show_all_pixels() {
    for (int i = 0; i < num_elements; i++) l_elements[i].show(crgb_leds, BRIGHTNESS);
    //FastLED.show();
}