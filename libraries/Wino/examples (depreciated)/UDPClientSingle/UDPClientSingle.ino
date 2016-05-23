/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* based on code by ITEAD Studio Teams (C) 2015 ITEADLIB_Arduino_WeeESP8266
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/

#include "wino.h"

#define SSID        "ITEAD"
#define PASSWORD    "12345678"
#define HOST_NAME   "172.16.5.12"
#define HOST_PORT   (5416)

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
    
    if (wifi.mux(0)) {
        SerialUSB.print("single ok\r\n");
    } else {
        SerialUSB.print("single err\r\n");
    }
    
    SerialUSB.print("setup end\r\n");
}
 
void loop(void)
{
    uint8_t buffer[128] = {0};
    
    if (wifi.connect("UDP",HOST_NAME, HOST_PORT)) {
        SerialUSB.print("register udp ok\r\n");
    } else {
        SerialUSB.print("register udp err\r\n");
    }
    
    char *hello = "Hello, this is client!";
    wifi.write((const uint8_t*)hello, strlen(hello));
    
    uint32_t len = wifi.read(buffer, sizeof(buffer), 10000);
    if (len > 0) {
        SerialUSB.print("Received:[");
        for(uint32_t i = 0; i < len; i++) {
            SerialUSB.print((char)buffer[i]);
        }
        SerialUSB.print("]\r\n");
    }
    
    if (wifi.disconnect()) {
        SerialUSB.print("unregister udp ok\r\n");
    } else {
        SerialUSB.print("unregister udp err\r\n");
    }
    delay(5000);
}
          