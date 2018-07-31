#include "Arduino.h"
#include "core/webupdate.h"
#include "core/onboard_led.h"
#include "core/oled_128x64.h"
#include "fun/conway.h"
#include "fun/rythm_blink.h"
#include "my_secrets.h"

RythmBlink rythm(
    "++.... +....+ +..... ...... ++.... +....+ +..... ......", // the 'bassline'
    false, // repeat?
    10, // LED glow time in ms
    100 // the shortest tone in the song (interval)
);

Conway conway(100 /*ms delay between pictures*/);

void setup() {
    Serial.begin(115200);
    Serial.println("");
    randomSeed((int)ESP8266_DREG(0x20E44)); // ESP8266 hardware randomizer
    WiFiConnection(MY_SSID, MY_WLAN_PASSWORD, MY_NODEMCU_WEB_USERNAME, MY_NODEMCU_WEB_PASSWORD);
    onboard_led::init();
    oled_display::init();
    oled_display::splashScreen();
    conway.init();
}

void loop() {
    httpServer.handleClient();
    rythm.play();
    conway.evolve();
}
