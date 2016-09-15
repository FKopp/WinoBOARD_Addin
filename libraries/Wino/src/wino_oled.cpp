/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/


#define WINO-OLED_CPP
#include "wino_oled.h"
#include "Wire.h"


#define LOG_OUTPUT_DEBUG            (1)
#define LOG_OUTPUT_DEBUG_PREFIX     (1)

#define logDebug(arg)\
    do {\
        if (LOG_OUTPUT_DEBUG)\
        {\
            if (LOG_OUTPUT_DEBUG_PREFIX)\
            {\
                SerialUSB.print("[LOG Debug: ");\
                SerialUSB.print((const char*)__FILE__);\
                SerialUSB.print(",");\
                SerialUSB.print((unsigned int)__LINE__);\
                SerialUSB.print(",");\
                SerialUSB.print((const char*)__FUNCTION__);\
                SerialUSB.print("] ");\
            }\
            SerialUSB.print(arg);\
        }\
    } while(0)
		
bool OLED_CLASS::init(void)
{
	//Adafruit_SSD1306 display(OLED_RESET);
	//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}   
	
bool OLED_CLASS::clear(void)
{
  /*  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);  */
}   
//Adafruit_SSD1306 display(A8);

//display.begin(SSD1306_SWITCHCAPVCC, 0x3C);