# nodemcu-core-stuff
Some handy tools for **my** first steps with NodeMCU v2.0 (Espressif 8266). This repo will grow the longer I toy around with the board.
I use Atom Editor with PlatformIO IDE to deploy my binaries onto the board.

# Installation
Just compile and upload with whatever IDE. I assume you are totally able to.

**Note:** To be able to connect to a WiFi and to login on the NodeMCU web interface you need a `my_secrets.h` file within the `src` folder.
It must contain the following constants:
``` c++
const char* MY_SSID = "the WiFi SSID";
const char* MY_WLAN_PASSWORD = "the WiFi password";
const char* MY_NODEMCU_WEB_USERNAME = "some cool username";
const char* MY_NODEMCU_WEB_PASSWORD = "some supersafe password";
```
This file is gitignored because it depends on your local settings. It won't be uploaded to the interwebs.

**Note:** The onboard LED pin number may differ on your board. Please set it accordingly within `core/onboard_led.h`. The `HIGH` and `LOW` values may also be dependend on your board.

