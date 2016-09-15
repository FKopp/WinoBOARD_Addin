/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/


#ifndef __WINO-OLED_H__
#define __WINO-OLED_H__
#endif

#include "Arduino.h"
//#include "utility/Adafruit_GFX.h"
#include "utility/Adafruit_SSD1306_wino.h"



class OLED_CLASS {
 public:

  
	bool init();
	bool clear();
};	

#define OLED_RESET A8
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#define OLED_ADDRESS  0x3C
#define OLED_TYPE  SSD1306_SWITCHCAPVCC
#define LOGO16_GLCD_WIDTH  16 

static const unsigned char PROGMEM logo16_glcd_bmp[] =
	{ B00100000, B11000000,
	  B00010001, B11000000,
	  B00000001, B11000100,
	  B00000011, B11100100,
	  B11110011, B11100000,
	  B11111110, B11111000,
	  B01111110, B11111111,
	  B00110011, B10011111,
	  B00011111, B11111100,
	  B00101101, B01110100,
	  B00011011, B10100000,
	  B00111111, B11100100,
	  B00111111, B11110000,
	  B01111100, B11110000,
	  B01110000, B01110000,
	  B00000000, B00110000 };
//extern OLED_CLASS oled;	  
//extern Adafruit_SSD1306 display(OLED_RESET);
#if defined WINO-OLED_CPP
	//Adafruit_SSD1306 display(A8);
   //Adafruit_SSD1306 display(A8);
#else
	extern Adafruit_SSD1306 display(A8);

#endif
