/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* based on code by ITEAD Studio Teams (C) 2015 ITEADLIB_Arduino_WeeESP8266
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "wino.h"

#define SSID        "ITEAD"
#define PASSWORD    "12345678"

void setup(void)
{
    SerialUSB.begin(9600);
    SerialUSB.print("setup begin\r\n");

    wifi.on();
    if(wifi.getStatus()) {
        SerialUSB.print("ESP8266 turned on\r\n");
    } else {
        SerialUSB.print("ESP8266 not woke up\r\n");
    }

    SerialUSB.print("FW Version: ");
    SerialUSB.println(wifi.info().c_str());
    
    
    if (wifi.setMode(0)) {
        SerialUSB.print("to station ok\r\n");
    } else {
        SerialUSB.print("to station err\r\n");
    }

    if (wifi.join(SSID, PASSWORD)) {
        SerialUSB.print("Join AP success\r\n");
        SerialUSB.print("IP: ");       
        SerialUSB.println(wifi.getIP().c_str());
    } else {
        SerialUSB.print("Join AP failure\r\n");
    }
    
    SerialUSB.print("setup end\r\n");
}

void loop(void)
{
}

