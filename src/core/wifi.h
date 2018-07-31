#ifndef CORE_WIFI_H
#define CORE_WIFI_H

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "my_secrets.h"

namespace wifi {
    void init()
    {
        Serial.println();
        Serial.println("Waiting for WiFi connection...");
        WiFi.mode(WIFI_AP_STA);
        do {
            WiFi.begin(MY_SSID, MY_WLAN_PASSWORD);
            Serial.print(".");
        } while(WiFi.waitForConnectResult() != WL_CONNECTED);
        Serial.print("connected. IP address: ");
        Serial.println(WiFi.localIP());
    }
}

#endif
