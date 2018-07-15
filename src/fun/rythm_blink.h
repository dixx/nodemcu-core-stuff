#ifndef RYTHM_BLINK_H
#define RYTHM_BLINK_H

#include <stdint.h>
#include "../core/onboard_led.h"

class RythmBlink {
public:
    RythmBlink(const char* rythm, const bool repeat = false)
    : rythm_(rythm),
      repeat_(repeat),
      count_(0),
      beatDuration_(100),
      beatDurationRest_(beatDuration_ - onboard_led::FLASH_DURATION)
    {}

    void next() {
        if (rythm_[count_] == '\0') {
            if (repeat_) {
                count_ = 0;
            } else {
                return;
            }
        }
        if (rythm_[count_] == '+') {
            onboard_led::flash();
            delay(beatDurationRest_);
        } else if (rythm_[count_] == '.') {
            delay(beatDuration_);
        } else {
            //nop
        }
        count_++;
    }

private:
    const char* rythm_;
    const bool repeat_;
    uint32_t count_;
    const uint32_t beatDuration_;
    const uint32_t beatDurationRest_;
};

#endif
