#ifndef CORE_OLED_DISPLAY_H
#define CORE_OLED_DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

namespace oled_display {
    namespace {
        bool ready = false;
    }

    Adafruit_SSD1306 display(-1);

    void init() {
        if (ready) return;
        display.begin();
        display.clearDisplay();
        display.display();
        ready = true;
    }

    void splashScreen() {
        display.drawPixel(0, 0, WHITE);
        display.drawPixel(127, 0, WHITE);
        display.drawPixel(0, 63, WHITE);
        display.drawPixel(127, 63, WHITE);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(28, 30);
        display.println("Guten Tag!");
        display.display();
        delay(1000);
        display.clearDisplay();
    }
}

#endif
