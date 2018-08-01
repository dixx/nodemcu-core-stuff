/*
    This class "plays" a rythm line over the onboard LED.
    Rythm lines can consist of `+` for a beat and `.` for a pause; any other char will be ignored.
    Use `myRhythm.play();` in your main loop, it will block only for a few processor ticks.
*/

#ifndef RYTHM_BLINK_H
#define RYTHM_BLINK_H

#include <stdint.h>
#include "Arduino.h"
#include "../core/onboard_led.h"
#include "../core/timer.h"

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
      stopPlayback_(false),
      timer_()
    {}

    void init() {
        onboard_led::init();
    }

    void play() {
        if (stopPlayback_ || timer_.isRunning()) return;
        if (onboard_led::isOn()) {
            continueNote();
        } else {
            continueRythm();
        }
    }

private:
    const char* rythm_;
    const bool repeat_;
    uint32_t position_;
    const uint32_t ledGlowDuration_;
    const uint32_t interval_;
    bool stopPlayback_;
    Timer timer_;

    void continueRythm() {
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

    void playNote() {
        if (rythm_[position_] == '+') {
            onboard_led::on();
            timer_.start(ledGlowDuration_);
        } else if (rythm_[position_] == '.') {
            timer_.start(interval_);
        } else {
            // just ignore all other chars
        }
    }

    void continueNote() {
        onboard_led::off();
        timer_.start(interval_ - ledGlowDuration_);
    }
};

#endif
