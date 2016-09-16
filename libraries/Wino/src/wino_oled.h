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

#define OLED_RESET A8

#if defined WINO-OLED_CPP

#else
	extern Adafruit_SSD1306 display(A8);

#endif
