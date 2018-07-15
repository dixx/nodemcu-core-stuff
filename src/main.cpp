#include "Arduino.h"
#include "core/webupdate.h"
#include "core/onboard_led.h"
#include "fun/rythm_blink.h"
#include "my_secrets.h"

RythmBlink rythm("++.... +....+ +..... ...... +...+. ..+... +..... ......", /*repeat == */ true);

void setup() {
    onboard_led::init();
    Serial.begin(115200);
    Serial.println("");
    WiFiConnection(MY_SSID, MY_WLAN_PASSWORD, MY_NODEMCU_WEB_USERNAME, MY_NODEMCU_WEB_PASSWORD);
}

void loop() {
    httpServer.handleClient();
    rythm.next();
}
