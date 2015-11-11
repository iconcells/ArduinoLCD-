#ifndef AXPLATFORM_H
#define AXPLATFORM_H

#include "AKPGenerator.h"
#include "Arduino.h"
#include "Stream.h"

class axPlatform
{
HardwareSerial *out;
AKPGenerator generator;

public:

axPlatform(HardwareSerial *dest);
void sendDataItem(char *name, int value);
void sendDataItem(char *name, boolean value);   //Equivalent to Digital
void sendDataItem(char *name, char *value);
void sendDataItem(char *name, String value);

void sendDataItem(String name, int value);
void sendDataItem(String name, boolean value);  //Equivalent to Digital
void sendDataItem(String name, char *value);
void sendDataItem(String name, String value);

void sendAlarm(String name, String description);
void sendAlarm(char *name, String description);
void sendAlarm(String name, char *description);
void sendAlarm(char *name, char *description);

void sendEvent(String eventName, String description);
void sendEvent(char *eventName, String description);
void sendEvent(String eventName, char *description);
void sendEvent(char *eventName, char *description);

void sendCommand(char *command);
void sendCommand(String command);

void sendError(char *errMsg);
void sendError(String errMsg);
};

#endif