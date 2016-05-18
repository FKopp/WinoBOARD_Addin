/*
* Copyright (C) 2015 Project http://www.wino-board.de/
* License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
*/
// #warning "wino.cpp v1.5 loaded"

#define WIDGETS_CPP
#include "widgets.h"
#include "wino.h"

const uint32_t maxwidgets = 10;

String description[maxwidgets];
int type[maxwidgets];
String unit[maxwidgets];
float minval[maxwidgets];
float maxval[maxwidgets];
String ondesc[maxwidgets];
String offdesc[maxwidgets];
float value[maxwidgets];



	bool WidgetClass::addSlider(uint32_t id, String Description, String Unit, float Minval, float Maxval ){   
		type[id] = 1;
		description[id] = Description;
		unit[id] = Unit;
		minval[id] = Minval;
		maxval[id] = Maxval;
	return true;

}
	bool WidgetClass::addSwitch(uint32_t id, String Description, String Ondesc, String Offdesc ){   
		type[id] = 2;
		description[id] = Description;
		ondesc[id] = Ondesc;
		offdesc[id] = Offdesc;
    return true;

}
	bool WidgetClass::addStatus(uint32_t id, String Description, String Unit ){   
		type[id] = 3;
		description[id] = Description;
		unit[id] = Unit;
    return true;

}
	bool WidgetClass::remove(uint32_t id){   

		description[id] = "";
		unit[id] = "";
		ondesc[id] = "";
		offdesc[id] = "";
	
    return true;

}
	bool WidgetClass::start(uint32_t port){   

	wifi.start(port);

    return true;

}
float WidgetClass::read(uint32_t id){   


	if (description[id] != ""){
		return value[id];
	}

    return 0;

}

bool WidgetClass::write(uint32_t id, float Value){   

	if (description[id] != ""){
			value[id] = Value;
	}

    return true;

}

bool WidgetClass::refresh() {

	String answer = "";
	int counter = 0;
	String data = wifi.readln(1000);
	
	if (data.indexOf("getdata") == 0){
		for (int i = 0; i <= maxwidgets; i++){
			if (description[i] != ""){counter++;}
		}
		if (counter > 0) {answer = "widgets:" + String(counter) + "\r\n";}
		for (int i = 0; i <= maxwidgets; i++){
			if (description[i] != ""){
				if (type[i] == 2){ //Switch-Widget
					int val = value[i];
					 answer = answer + String(i) + ";" + String(type[i]) + ";" + description[i] + ";" + String(val) + ";" + ondesc[i] + ";" + offdesc[i] + "\r\n";
				}
				else if (type[i] == 3){ //Status-Widget
			
					answer = answer + String(i) + ";" + String(type[i]) + ";" + description[i] + ";" + String(value[i],2) + ";" + unit[i] + "\r\n";
					//answer = answer + String(i) + ";" + String(type[i]) + ";" + description[i] + ";" + String(val) + ";" + unit[i] + "\r\n";
				}
				else if (type[i] == 1){ //Slider-Widget

					answer = answer + String(i) + ";" + String(type[i]) + ";" + description[i] + ";" + String(value[i],2) + ";" + unit[i] + ";" + String(minval[i],2) + ";" + String(maxval[i],2) + "\r\n";
					//answer = answer + String(i) + ";" + String(type[i]) + ";" + description[i] + ";" + String(val) + ";" + unit[i] + ";" + String(valmin) + ";" + String(valmax) + "\r\n";
				}
				else {return false;}
			}
		}
		wifi.writeln(answer);
	}
	if (data.indexOf("setdata(") == 0){
		int Id = 0;
		float Value = 0;
		Id = (data.substring(data.indexOf("(") + 1, data.indexOf(";"))).toInt();
		Value = (data.substring(data.indexOf(";") + 1, data.indexOf(")"))).toFloat();
		value[Id] = Value;
		//wifi.writeln("Value: " + String(Value));
		//wifi.writeln("ID: " + String(Id));
		//wifi.writeln("OK");
	}
	return true;
}

WidgetClass widget;
