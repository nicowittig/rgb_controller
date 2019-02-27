//
// Created by Nico Wittig on 2018-12-13.
//

#include "controller.h"


void controller::setup() {
    Serial.begin(9600);
    Serial.println("START");

    pinMode(10, INPUT_PULLUP);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);

    cur_mode = 255;
    new_mode = EEPROM.read(EEPROM_MODE_ADDRESS);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(crgb_leds, NUM_LEDS);
    for (auto &crgb_led : crgb_leds) crgb_led = CRGB::Black;
    for (auto &effect : effects) effect = nullptr;

    light_elements[0] = light_element(0, NUM_LEDS);

    ir_sensors[0] = new input_analog(4, 100, .025, true);
    ir_sensors[0]->adjust_trigger_value();

    button[0] = new input_digital(5, true, true);

    show_all_pixels();
}


void controller::loop() {

#ifdef DEBUG
    Serial.print("RAM: ");
    Serial.print(freeRam());
    Serial.print(" | ");
    Serial.print("MODE: ");
    Serial.print(cur_mode);
    Serial.print(" | ");
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        Serial.print(i);
        Serial.print(": ");
        if (effects[i] != nullptr) Serial.print(effects[i]->getName());
        Serial.print(" | ");
    }
    Serial.println();
#endif

#ifdef DEBUG1
    Serial.print(button[0]->is_pushed());
    Serial.print(" | ");
    Serial.print(button[0]->is_toggled());
    Serial.print(" | ");
    Serial.print(button[0]->is_tapped());
    Serial.print(" | ");
    Serial.print(button[0]->is_changed());
    Serial.print(" | ");
    button[0]->print_to_serial();
#endif
#ifdef DEBUG2
    Serial.print(ir_sensors[0]->is_pushed());
    Serial.print(" | ");
    Serial.print(ir_sensors[0]->is_toggled());
    Serial.print(" | ");
    Serial.print(ir_sensors[0]->is_tapped());
    Serial.print(" | ");
    Serial.print(ir_sensors[0]->is_changed());
    Serial.print(" | ");
    ir_sensors[0]->print_to_serial();
#endif

    if (Serial.available() > 0) {
        char message = Serial.read();
        Serial.print("Received serial message: ");
        Serial.println(message);

        switch(message) {
            case 't': setup(); break;
            case 'r':
                soft_reset(); break;
            case 'w': setBrightness(brightness+0.1f); break;
            case 's': setBrightness(brightness-0.1f); break;
            default: break;
        }

        if ((message - 48) >= 0 && (message - 48) <= 9) new_mode = (uint8_t) (message - 48);
    }

    if (cur_mode != new_mode) {

#ifdef DEBUG
        Serial.print("new Mode: ");
        Serial.println(new_mode);
#endif
        cur_mode = new_mode;
        mode_init(&cur_mode);
    }

    mode_run(&cur_mode);

    show_all_pixels();

    refresh_inputs();

    if (freeRam() < 200) soft_reset();
}


void controller::mode_init(uint8_t *mode) {
    for (auto &effect : effects) {
        if (effect != nullptr) {
            delete(effect);
            effect = nullptr;
        }
    }

    switch (*mode) {
        case 0 : {
            effects[0] = new e_static_color(&light_elements[0], CHSV(0, 255, 0));
            break;
        }
        case 1 : {
            effects[0] = new e_static_color(&light_elements[0], CHSV(0,255,255), CHSV(96,255,255), true);
            break;
        }
        case 2 : {
            effects[0] = new e_rainbow_shift(&light_elements[0]);
            break;
        }
        case 3 : {
            effects[0] = new e_fire(&light_elements[0], 55, 120);
            break;
        }
        case 4 : {
            CRGB colors[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
            effects[0] = new e_bouncing_balls(&light_elements[0], 3, colors);
            break;
        }
        case 5 : { // Test effect
            for (int i = 0; i < light_elements[0].get_num_leds(); i++) light_elements[0].leds[i] = CHSV (i, 255, 255);
            break;
        }
        default: new_mode = 0;
    }

    for (auto &effect : effects) {
        if (effect == nullptr) continue;
        effect->init();
    }

    EEPROM.update(EEPROM_MODE_ADDRESS, *mode);
}


void controller::mode_run(uint8_t *mode) {
    switch(*mode) {
        case 2 : {
            delay(70);
            break;
        }
        case 3 : {
            delay(15);
            break;
        }
        case 5 : { // Test effect
            for (int i = 0; i < light_elements[0].get_num_leds(); i++) light_elements[0].leds[i].hue++;
            break;
        }
        default: break;
    }

    for (auto &effect : effects) {
        if (effect == nullptr) continue;
        effect->run();
    }
}


void controller::mode_led(uint8_t *mode) {
    // TODO
}


void controller::refresh_inputs() {
    ir_sensors[0]->refresh_state();
    button[0]->refresh_state();
}
