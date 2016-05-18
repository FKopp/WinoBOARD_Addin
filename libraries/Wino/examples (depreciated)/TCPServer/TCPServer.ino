/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* based on code by ITEAD Studio Teams (C) 2015 ITEADLIB_Arduino_WeeESP8266
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "wino.h"

#define SSID        "Mitsu"
#define PASSWORD    "murasame"

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

    SerialUSB.print("FW Version:");
    SerialUSB.println(wifi.info().c_str());
      
    if (wifi.setMode(2)) {
        SerialUSB.print("to station + softap ok\r\n");
    } else {
        SerialUSB.print("to station + softap err\r\n");
    }
 
    if (wifi.join(SSID, PASSWORD)) {
        SerialUSB.print("Join AP success\r\n");
        SerialUSB.print("IP: ");
        SerialUSB.println(wifi.getIP().c_str());    
    } else {
        SerialUSB.print("Join AP failure\r\n");
    }
    
    if (wifi.mux(1)) {
        SerialUSB.print("multiple ok\r\n");
    } else {
        SerialUSB.print("multiple err\r\n");
    }
    
    if (wifi.start(8090)) {
        SerialUSB.print("start tcp server ok\r\n");
    } else {
        SerialUSB.print("start tcp server err\r\n");
    }
    
    if (wifi.setTCPServerTimeout(10)) { 
        SerialUSB.print("set tcp server timout 10 seconds\r\n");
    } else {
        SerialUSB.print("set tcp server timout err\r\n");
    }
    
    SerialUSB.print("setup end\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    uint8_t mux_id;
    uint32_t len = wifi.read(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        SerialUSB.print("Status:[");
        SerialUSB.print(wifi.getIPStatus().c_str());
        SerialUSB.println("]");
        
        SerialUSB.print("Received from :");
        SerialUSB.print(mux_id);
        SerialUSB.print("[");
        for(uint32_t i = 0; i < len; i++) {
            SerialUSB.print((char)buffer[i]);
        }
        SerialUSB.print("]\r\n");
        
        if(wifi.write(mux_id, buffer, len)) {
            SerialUSB.print("send back ok\r\n");
        } else {
            SerialUSB.print("send back err\r\n");
        }
        
        if (wifi.disconnect(mux_id)) {
            SerialUSB.print("release tcp ");
            SerialUSB.print(mux_id);
            SerialUSB.println(" ok");
        } else {
            SerialUSB.print("release tcp");
            SerialUSB.print(mux_id);
            SerialUSB.println(" err");
        }
        
        SerialUSB.print("Status:[");
        SerialUSB.print(wifi.getIPStatus().c_str());
        SerialUSB.println("]");
    }
}
        
