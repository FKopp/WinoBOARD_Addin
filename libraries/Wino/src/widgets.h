/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/
// #warning "wino.h v1.4 loaded"

#ifndef __WIDGETS_H__
#define __WIDGETS_H__

#include "Arduino.h"


class WidgetClass {
 public:
 
	bool addSlider(uint32_t id, String Description, String Unit, float Minval, float Maxval );
	bool addSwitch(uint32_t id, String Description, String Ondesc, String Offdesc );
	bool addStatus(uint32_t id, String Description, String Unit );
	bool remove(uint32_t id);
	bool write(uint32_t id, float Value);
	float read(uint32_t id);
	bool start(uint32_t port = 7777);
	bool refresh();
};
  
#endif

extern WidgetClass widget;