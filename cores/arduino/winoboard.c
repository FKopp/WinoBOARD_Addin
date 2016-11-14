/*
  Copyright (c) 2016 Florian Kopp.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

// sends the MCU to sleep in the defined sleepmode
void sleep(uint8_t mode)
{
	
	switch (mode) {
		case 0:
			 system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE_0); //CPU clock off
			break;
		case 1:
			 system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE_1); //CPU clock, AHB clock off
			break;
		case 2:
			 system_set_sleepmode(SYSTEM_SLEEPMODE_IDLE_2); //CPU clock, AHB clock, APB clock off
			break;
		case 3:
			 system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY); //MCU in standby, waiting for interrupt
			break;

		default:
			return;
	}	
  
 system_sleep();  //send MCU to sleep
 
 
}
