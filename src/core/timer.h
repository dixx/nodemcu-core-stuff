/*
    This class provides a very simple timer.
    It takes into account that `millis()` overflows after 49 days.
*/

#ifndef CORE_TIMER_H
#define CORE_TIMER_H

#include <stdint.h>
#include "Arduino.h"

class Timer {
public:
    Timer() = default;

    void start(uint32_t duration) {
        then_ = millis() + duration;
    }

    const bool isRunning() const {
        return then_ > millis();
    }

private:
    uint32_t then_ = 0;
};

#endif
