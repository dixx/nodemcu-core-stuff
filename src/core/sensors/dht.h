#ifndef CORE_SENSORS_DHT_H
#define CORE_SENSORS_DHT_H

#include <stdint.h>
#include <Arduino.h>
#include <Ticker.h>
#include <DHT.h>

namespace dht {
    namespace {
        bool ready = false;
        Ticker ticker;
        DHT11 sensor;
        volatile int8_t result = 0;
    }

    void readDHT() {
      sensor.read();
    }

    void init()
    {
        if (ready) return;
        serial::init();
        sensor.setPin(D8);
        ticker.attach(30, readDHT);
        ready = true;
    }

    void check() {
        result = sensor.ready();
        if (result == 0) {
            return;
        } else if (result == 1) {
            Serial.printf("Temp: %.1f°C\n", sensor.getTemperature());
            Serial.printf("Humid: %.1f%%\n", sensor.getHumidity());
        } else if (result == -1) {
            Serial.println("DHT sensor timed out");
        } else if (result == -2) {
            Serial.println("DHT sensor NACK error");
        } else if (result == -3) {
            Serial.println("DHT sensor DATA error");
        } else if (result == -4) {
            Serial.println("DHT sensor checksum error");
        }
    }
}

#endif
