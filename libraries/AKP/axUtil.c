#include "Arduino.h"

int freeRam()
	{
	//This function will report back how many bytes are available in the Arduino's heap.
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
	}


