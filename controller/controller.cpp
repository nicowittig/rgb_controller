//
// Created by Nico Wittig on 2018-12-13.
//

#include "controller.h"


void controller::setup() {
    Serial.begin(9600);

    pinMode(10, INPUT_PULLUP);
    pinMode(12, OUTPUT);
    digitalWrite(12, LOW);

    cur_mode = 255;
    new_mode = EEPROM.read(EEPROM_MODE_ADDRESS);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(crgb_leds, NUM_LEDS);
    for (auto &crgb_led : crgb_leds) crgb_led = CRGB::Black;

    l_elements[0] = light_element(0, 77);

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
        Serial.print(effects[i]->getName());
        Serial.print(" | ");
    }
    Serial.println();

    if (Serial.available() > 0) {
        char message = Serial.read();
        Serial.print("Received serial message: ");
        Serial.println(message);

        switch(message) {
            case 't': setup(); break;
            case 'r': softReset(); break;
            case 'w': setBrightness(brightness+0.1f); break;
            case 's': setBrightness(brightness-0.1f); break;
            default: break;
        }

        if ((message - 48) >= 0 && (message - 48) <= 9) new_mode = (uint8_t) (message - 48);
    }
#endif

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
    if (freeRam() < 200) softReset();
}


void controller::mode_init(uint8_t *mode) {
    //for (auto &effect : effects) delete(effect);
    //for (int i = 0; i < NUM_ELEMENTS; i++) delete(effects[0]);

    switch (cur_mode) {
        case 0 : {
            effects[0] = new e_static_color(&l_elements[0], CHSV(0, 255, 0));
            effects[0]->init();
            break;
        }
        case 1 : {
            effects[0] = new e_static_color(&l_elements[0], CHSV(230, 255, 255));
            effects[0]->init();
            break;
        }
        case 2 : {
            effects[0] = new e_rainbow_shift(&l_elements[0]);
            effects[0]->init();
            break;
        }
        case 3 : {
            effects[0] = new e_fire(&l_elements[0], 55, 120);
            effects[0]->init();
            break;
        }
        case 4 : {
            CRGB colors[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
            effects[0] = new e_bouncing_balls(&l_elements[0], 3, colors);
            effects[0]->init();
            break;
        }
        default: new_mode = 0;
    }

    EEPROM.write(EEPROM_MODE_ADDRESS, cur_mode);
}


void controller::mode_run(uint8_t *mode) {
    switch(cur_mode) {
        case 0 : break;
        case 1 : break;
        case 2 : {
            effects[0]->run();
            delay(70);
            break;
        }
        case 3 : {
            effects[0]->run();
            delay(15);
            break;
        }
        case 4 : {
            effects[0]->run();
            break;
        }
        default: break;
    }
}


void controller::mode_led(uint8_t *mode) {
    // TODO
}
