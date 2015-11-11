#include "axPlatform.h"

axPlatform::axPlatform(HardwareSerial *dest)
  {
   out=dest;
  }

/*==========================================[DATA ITEM METHODS]======================*/
void axPlatform::sendDataItem(char *name, int value)
  {
  String msg=String(generator.AKP_getDataMessage(String(name), long(value)));
  out->print(msg);
  }
void axPlatform::sendDataItem(char *name, boolean value) //Equivalent to Digital
  {
  String msg=String(generator.AKP_getDataMessage(String(name), value));
  out->print(msg);
  }   
void axPlatform::sendDataItem(char *name, char *value)
  {
  String msg=String(generator.AKP_getDataMessage(String(name), String(value)));
  out->print(msg);
  }
void axPlatform::sendDataItem(char *name, String value)
  {
  String msg=String(generator.AKP_getDataMessage(String(name), value));
  out->print(msg);
  }

void axPlatform::sendDataItem(String name, int value)
  {
  String msg=String(generator.AKP_getDataMessage(name, long(value)));
  out->print(msg);
  }
void axPlatform::sendDataItem(String name, boolean value)  //Equivalent to Digital
  {
  String msg=String(generator.AKP_getDataMessage(name, value));
  out->print(msg);
  }
void axPlatform::sendDataItem(String name, char *value)
  {
  String msg=String(generator.AKP_getDataMessage(name, String(value)));
  out->print(msg);
  }
void axPlatform::sendDataItem(String name, String value)
  {
  String msg=String(generator.AKP_getDataMessage(name, value));
  out->print(msg);
  }
/*==========================================[ALARM METHODS]======================*/
void axPlatform::sendAlarm(String name, String description)
  {
  String msg=String(generator.AKP_getAlarmMessage(name, description));
  out->print(msg);
  }
void axPlatform::sendAlarm(char *name, String description)
  {
  String msg=String(generator.AKP_getAlarmMessage(String(name), description));
  out->print(msg);
  }
void axPlatform::sendAlarm(String name, char *description)
  {
  String msg=String(generator.AKP_getAlarmMessage(name, String(description)));
  out->print(msg);
  }
void axPlatform::sendAlarm(char *name, char *description)
  {
  String msg=String(generator.AKP_getAlarmMessage(String(name), String(description)));
  out->print(msg);
  }
/*==========================================[EVENT METHODS]======================*/
void axPlatform::sendEvent(String eventName, String description)
  {
  String msg=String(generator.AKP_getEventMessage(String(eventName), String(description)));
  out->print(msg);
  }
void axPlatform::sendEvent(char *eventName, String description)
  {
  String msg=String(generator.AKP_getEventMessage(String(eventName), description));
  out->print(msg);
  }
void axPlatform::sendEvent(String eventName, char *description)
  {
  String msg=String(generator.AKP_getEventMessage(eventName, String(description)));
  out->print(msg);
  }
void axPlatform::sendEvent(char *eventName, char *description)
  {
  String msg=String(generator.AKP_getEventMessage(String(eventName), String(description)));
  out->print(msg);
  }

/*==========================================[COMMAND METHODS]======================*/
  
void axPlatform::sendCommand(char *command)
  {
  String msg=String(generator.AKP_getCommandMessage(String(command)));
  out->print(msg);
  }
void axPlatform::sendCommand(String command)
  {
  String msg=String(generator.AKP_getCommandMessage(command));
  out->print(msg);
  }
/*==========================================[ERROR METHODS]======================*/  
void axPlatform::sendError(char *errMsg)
  {
  String msg=String(generator.AKP_getErrorMessage(String(errMsg)));
  out->print(msg);
  }
void axPlatform::sendError(String errMsg)
  {
   String msg=String(generator.AKP_getErrorMessage(errMsg));
  out->print(msg);
  }