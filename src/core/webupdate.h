#ifndef CORE_WEBUPDATE_H
#define CORE_WEBUPDATE_H

#include "Arduino.h"
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include "core/webserver.h"
#include "my_secrets.h"

namespace webupdater {
    ESP8266HTTPUpdateServer httpUpdater;

    void init()
    {
        MDNS.begin("esp8266-webupdate");
        httpUpdater.setup(&webserver::server, MY_NODEMCU_WEB_USERNAME, MY_NODEMCU_WEB_PASSWORD);
        webserver::server.begin();
        //MDNS.addService("http", "tcp", 80);
        Serial.println("HTTPUpdateServer ready!");
    }
}

#endif
