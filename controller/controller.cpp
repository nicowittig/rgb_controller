//
// Created by Nico Wittig on 2018-12-13.
//

#include "controller.h"


void controller::setup() {
    Serial.begin(4800);

    cur_mode = 255;
    new_mode = 1;

    FastLED.addLeds<WS2812, LED_PIN, GRB>(crgb_leds, NUM_LEDS);
    for (auto &crgb_led : crgb_leds) crgb_led = CRGB::Black;

    l_elements[0] = light_element(0, 15);

    show_all_pixels();
}

void controller::loop() {

    if (Serial.available() > 0) {
        char message = Serial.read();
        Serial.print("Received serial message: ");
        Serial.println(message);

        switch(message) {
            case 'r': {
                setup();
                break;
            }

            default: break;
        }

        if ((message - 48) >= 0 && (message - 48) <= 9) new_mode = (uint8_t) (message - 48);
    }




    if (new_mode != cur_mode) {

        for (auto &effect : effects) delete(effect);

        switch (new_mode) {
            case 0 : {
                effects[0] = new e_fire(&l_elements[0], 55, 120);
                effects[0]->init();
                break;
            }
            case 1 : {
                CRGB colors[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
                effects[0] = new e_bouncing_balls(&l_elements[0], 3, colors, crgb_leds);
                effects[0]->init();
                break;
            }
            default: break;
        }

        cur_mode = new_mode;
    }


    switch(cur_mode) {
        case 0 : {
            effects[0]->run();
            delay(15);
            break;
        }
        case 1 : {
            effects[0]->run();
            break;
        }
        default: break;
    }


















    Serial.println(freeRam());
    show_all_pixels();
    delay_counter++;
}

//region Getter & Setter

uint8_t controller::get_mode() const {
    return cur_mode;
}

void controller::set_mode(uint8_t mode) {
    this->new_mode = mode;
}

float controller::getBrightness() const {
    return brightness;
}

bool controller::setBrightness(float brightness) {
    if (brightness < 0 || brightness > 1) return false;
    this->brightness = brightness;
    return true;
}

//endregion

void controller::adjust_sensors() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].adjust_trigger_value();
    //Serial.println("[Sensor-Reset]");
}

void controller::refresh_inputs() {
    //for (int i = 0; i < num_ir_sensors; i++) ir_sensors[i].refresh_state();
    //microphone[0].refresh_state();
}

void controller::show_all_pixels() {
    for (int i = 0; i < num_elements; i++) l_elements[i].show(crgb_leds, brightness);
    FastLED.show();
}