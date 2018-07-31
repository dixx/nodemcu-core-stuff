/*
    This class plays Conways Game Of Life over a connected OLED 128x64 display.
    Use `myConway.evolve();` in your main loop, it will block only for a few processor ticks.
*/

#ifndef CONWAY_H
#define CONWAY_H

#include <stdint.h>
#include "Arduino.h"
#include "../core/timer.h"
#include "../core/oled_128x64.h"

class Conway {
public:
    Conway(const uint32_t delay) : delay_(delay), timer_() {};

    void init() {
        for (uint8_t x = 0; x < MAX_X; ++x) {
            for (uint8_t y = 0; y < MAX_Y; ++y) {
                backupBuffer_[x][y] = false;
                if (x == 0 || y == 0 || x == MAX_X - 1 || y == MAX_Y - 1) continue;
                drawBuffer_[x][y] = (random(0, 4) == 0);
            }
        }
        display();
        timer_.start(delay_);
    }

    void evolve() {
        if (timer_.isRunning()) return;
        timer_.start(delay_);
        liveOrDie();
        display();
    }

private:
    static const uint8_t MAX_X = 32;
    static const uint8_t MAX_Y = 16;
    uint32_t delay_;
    bool drawBuffer_[MAX_X][MAX_Y];
    bool backupBuffer_[MAX_X][MAX_Y];
    Timer timer_;

    void display() {
        for (uint8_t x = 0; x < MAX_X; ++x) {
            for (uint8_t y = 0; y < MAX_Y; ++y) {
                oled_display::display.fillRect(x*4, y*4, x*4 + 3, y*4 + 3, (drawBuffer_[x][y] == true) ? WHITE : BLACK);
            }
        }
        oled_display::display.display();
    }

    void saveBackupBuffer() {
        for (uint8_t x = 0; x < MAX_X; ++x) {
            for (uint8_t y = 0; y < MAX_Y; ++y) {
                backupBuffer_[x][y] = drawBuffer_[x][y];
            }
        }
    }

    void liveOrDie() {
        saveBackupBuffer();
        for (uint8_t x = 1; x < (MAX_X - 1); ++x) {
            for (uint8_t y = 1; y < (MAX_Y - 1); ++y) {
                uint8_t neighbours = countNeighbours(x, y);
                if (neighbours < 2) drawBuffer_[x][y] = false;
                else if (neighbours > 3) drawBuffer_[x][y] = false;
                else if (neighbours == 3) drawBuffer_[x][y] = true;
            }
        }
    }

    const uint8_t countNeighbours(const uint8_t x, const uint8_t y) const {
        uint8_t neighbours = 0;
        for (int8_t c = -1; c < 2; ++c) {
            for (int8_t d = -1; d < 2; ++d) {
                if (!(c == 0 && d == 0) && backupBuffer_[x + c][y + d] == true) neighbours++;
            }
        }
        return neighbours;
    }
};

#endif
