/*
    This class "plays" a rythm line over the onboard LED.
    Rythm lines can consist of `+` for a beat and `.` for a pause; any other char will be ignored.
    It will pause the main loop only for a few processor ticks.
*/

#ifndef RYTHM_BLINK_H
#define RYTHM_BLINK_H

#include <stdint.h>
#include "Arduino.h"
#include "../core/onboard_led.h"

class RythmBlink {
public:
    RythmBlink(
        const char* rythm,
        const bool repeat = false,
        const uint32_t ledGlowDuration = 10,
        const uint32_t interval = 100
    )
    : rythm_(rythm),
      repeat_(repeat),
      position_(0),
      ledGlowDuration_(ledGlowDuration), // ms
      interval_(interval), // ms
      rest_(interval - ledGlowDuration), // ms
      last_(millis()), // ms, timestamp from last musical note
      duration_(0),
      ledIsOn_(false),
      stopPlayback_(false)
    {}

    // TODO own cpp file, use timer to unblock main loop(), check coding guidelines

    void play() {
        if (stopPlayback_ || noUpdateNeeded()) return;
        if (ledIsOn_) {
            onboard_led::off();
            ledIsOn_ = false;
            duration_ = rest_;
        } else {
            if (rythm_[position_] == '\0') {
                if (repeat_) {
                    position_ = 0;
                } else {
                    stopPlayback_ = true;
                    return;
                }
            }
            playNote();
            position_++;
        }
        last_ = millis();
    }

private:
    const char* rythm_;
    const bool repeat_;
    uint32_t position_;
    const uint32_t ledGlowDuration_;
    const uint32_t interval_;
    const uint32_t rest_;
    uint32_t last_;
    uint32_t duration_;
    bool ledIsOn_; // TODO outsource this state to onboard_led.h
    bool stopPlayback_;

    const bool noUpdateNeeded() const {
        return (last_ + duration_) > millis();
    }

    void playNote() {
        if (rythm_[position_] == '+') {
            onboard_led::on();
            duration_ = ledGlowDuration_;
            ledIsOn_ = true;
        } else if (rythm_[position_] == '.') {
            duration_ = interval_;
        } else {
            // just ignore all other chars
        }
    }
};

#endif
