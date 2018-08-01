#include "Arduino.h"
#include "core/oled_128x64.h"
#include "core/webserver.h"
#include "core/webupdate.h"
#include "core/wifi.h"
#include "fun/conway.h"
#include "fun/rythm_blink.h"

RythmBlink rythm(
    "++.... +....+ +..... ...... ++.... +....+ +..... ......", // the 'bassline'
    false, // repeat?
    10, // LED glow time in ms
    100 // the shortest tone in the song (interval)
);

Conway conway(500 /*ms delay between generations*/);

void setup() {
    randomSeed((int)ESP8266_DREG(0x20E44)); // ESP8266 hardware randomizer
    wifi::init();
    webserver::init();
    webupdater::init();
    oled_display::init();
    oled_display::splashScreen();
    rythm.init();
    conway.init();
}

void loop() {
    webserver::server.handleClient();
    rythm.play();
    conway.evolve();
}
