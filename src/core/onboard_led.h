#ifndef ONBOARD_LED_H
#define ONBOARD_LED_H

#include <stdint.h>
#include "Arduino.h"

namespace onboard_led {
    const uint32_t FLASH_DURATION = 10; // ms
    const uint32_t ONBOARD_LED = D4;

    void on() {
        digitalWrite(ONBOARD_LED, LOW);
    }

    void off() {
        digitalWrite(ONBOARD_LED, HIGH);
    }

    void flash() {
        on();
        delay(FLASH_DURATION);
        off();
    }

    void init() {
        pinMode(ONBOARD_LED, OUTPUT);
        off();
    }
}

#endif
