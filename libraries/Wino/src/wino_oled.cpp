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
		
