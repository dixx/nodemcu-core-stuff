#include "Arduino.h"
#include "core/onboard_led.h"
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
    Serial.begin(115200);
    delay(5000);
    Serial.println("");
    randomSeed((int)ESP8266_DREG(0x20E44)); // ESP8266 hardware randomizer
    wifi::init();
    webserver::init();
    webupdater::init();
    onboard_led::init();
    oled_display::init();
    oled_display::splashScreen();
    conway.init();
}

void loop() {
    webserver::server.handleClient();
    rythm.play();
    conway.evolve();
}
