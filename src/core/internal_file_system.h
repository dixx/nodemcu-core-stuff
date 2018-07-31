#ifndef CORE_INTERNAL_FILE_SYSTEM_H
#define CORE_INTERNAL_FILE_SYSTEM_H

#include <FS.h>

namespace spiffs {
    void init() {
        SPIFFS.begin();
        Dir dir = SPIFFS.openDir("/");
        Serial.println("Files in SPIFFS:");
        while (dir.next()) {
            Serial.print("  " + dir.fileName() + " (");
            File f = dir.openFile("r");
            Serial.print(f.size());
            Serial.println(" Byte)");
        }
    }
}

#endif
