/* ========================================================================== */
/*                                                                            */
/*   AKPMessage.h                                                             */
/*   (c) 2013 Chris Meringolo                                                 */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */
#ifndef AKPMESSAGE_H
#define AKPMESSAGE_H

#include <Arduino.h>
#include "AKPMessageConstants.h"
#include "AKPGenerator.h"


class AKPMessage
{
protected:     
   MsgType msgType;

   int validMessage;
   

public:
    AKPMessage();
   // AKPMessage(int type);
    AKPMessage(MsgType type);
    AKPMessage(MsgType type, char *in_name, char *in_value);
    
    char *name;
   char *value;
   char *rawMessage;
    
    int isAlarm();
    int isData();
    int isEvent();
    int isError();
    int isCommand();
    int isSystemRegistration();
    
    void setType(char *typ);
    void setType(MsgType typ);
    
    void setName(char *newName);
    void setValue(char *newValue);
    void setRawMessage(char *newMsg);
    char *toAKPString();
    char *toString(); 
    void setValid(int valid);
    const char *getTypeAsChar();   
};

#endif


