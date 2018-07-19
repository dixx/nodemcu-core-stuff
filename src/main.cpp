#include "Arduino.h"
#include "core/webupdate.h"
#include "core/onboard_led.h"
#include "core/oled_128x64.h"
#include "fun/rythm_blink.h"
#include "my_secrets.h"

RythmBlink rythm(
    "++.... +....+ +..... ...... ++.... +....+ +..... ......", // the 'bassline'
    false, // repeat?
    10, // LED glow time in ms
    100 // the shortest tone in the song (interval)
);

void setup() {
    Serial.begin(115200);
    Serial.println("");
    WiFiConnection(MY_SSID, MY_WLAN_PASSWORD, MY_NODEMCU_WEB_USERNAME, MY_NODEMCU_WEB_PASSWORD);
    onboard_led::init();
    oled_display::init();
    oled_display::splashScreen();
}

void loop() {
    httpServer.handleClient();
    rythm.play();
}
