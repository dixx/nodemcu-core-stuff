#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTION_H

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void WiFiConnection(const char* ssid, const char* password, const char* update_username, const char* update_password)
{
    Serial.println();
    Serial.println("Waiting for WiFi connection...");
    WiFi.mode(WIFI_AP_STA);
    do {
        WiFi.begin(ssid, password);
        Serial.print(".");
    } while(WiFi.waitForConnectResult() != WL_CONNECTED);
    Serial.println("connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    MDNS.begin("esp8266-webupdate");
    httpUpdater.setup(&httpServer, update_username, update_password);
    httpServer.begin();
    //MDNS.addService("http", "tcp", 80);
    Serial.printf("HTTPUpdateServer ready!");
}

#endif
