/* ========================================================================== */
/*                                                                            */
/*   AKPMessage.c                                                             */
/*   (c) 2012 Author                                                          */
/*                                                                            */
/*   Implementation of the AxedaKegBot Protocol for Arduino.                  */
/*                                                                            */
/* ========================================================================== */

#include "AKPMessage.h"
#include "AKPMessageConstants.h"

//=============FIELD REFERENCE//
//   const char msgType;
//   char *name
//   char *value
//   char* rawMessage;
//   int validMessage;


//=============PRIVATE METHODS==============================


//=============PUBLIC METHODS===============================

    AKPMessage::AKPMessage()
      {
      msgType=ERROR;
      name = (char *)malloc(sizeof(char)*5);
      strcpy(name, "null");
      name[4]='\0';
      value = (char *)malloc(sizeof(char)*5);
      strcpy(value, "null");
      value[4]='\0';
      validMessage=0;
      }
    AKPMessage::AKPMessage(MsgType type)
      {
      msgType=type;
      name = (char *)malloc(sizeof(char)*5);
      strcpy(name, "null");
      name[4]='\0';
      value = (char *)malloc(sizeof(char)*5);
      strcpy(value, "null");
      value[4]='\0';
      validMessage=1;
      }
    AKPMessage::AKPMessage(MsgType type, char *in_name, char *in_value)
      {
      msgType=type;
      int name_sz=strlen(in_name);
      int value_sz=strlen(in_value);
      name=(char *)malloc(sizeof(char)*name_sz);
      strcpy(name, in_name);
      name[name_sz]='\0';
      value=(char *)malloc(sizeof(char)*value_sz);
      strcpy(value, in_value);
      value[value_sz]='\0';
      validMessage=1;
      }
    
    int AKPMessage::isAlarm()
      {
      if (msgType == ALARM)
        return 1;
      else
        return 0;

      }
      
    int AKPMessage::isData()
      {
      if ((msgType == DATA_STRING)||(msgType == DATA_ANALOG)||(msgType == DATA_BOOLEAN))
        return 1;
      else
        return 0;
      }
    int AKPMessage::isEvent()
      {
      if (msgType == EVENT)
        return 1;
      else
        return 0;
      }
    int AKPMessage::isError()
      {
      if (msgType == ERROR)
        return 1;
      else
        return 0;
      }
    int AKPMessage::isCommand()
      {
      if (msgType == COMMAND)
        return 1;
      else
        return 0;
      }
    int AKPMessage::isSystemRegistration()
      {
      if (msgType == SYSREG)
        return 1;
      else
        return 0;
      }
    
    void AKPMessage::setType(char *typ)
      {
      
      if (strcmp(typ, AKP_ALARM)==0) {msgType=ALARM; return;}
      if (strcmp(typ, AKP_DATA_STRING)==0) {msgType=DATA_STRING; return;}
      if (strcmp(typ, AKP_DATA_ANALOG)==0) {msgType=DATA_ANALOG;return;}
      if (strcmp(typ, AKP_DATA_BOOLEAN)==0) {msgType=DATA_BOOLEAN; return;}
      if (strcmp(typ, AKP_EVENT)==0) {msgType=EVENT; return;}
      if (strcmp(typ, AKP_ERROR)==0) {msgType=ERROR; return;}
      if (strcmp(typ, AKP_COMMAND)==0) {msgType=COMMAND; return;}
      if (strcmp(typ, AKP_SYSREG)==0) {msgType=SYSREG; return;}
      
      }
    void AKPMessage::setType(MsgType typ)
      {
      msgType=typ;
      }
      
      void AKPMessage::setName(char *newName)
        {
         if(name != NULL)
           {
           free(name);
           }
        name=(char *)malloc(sizeof(char)*strlen(newName));
        strcpy(name, newName);
        }

      void AKPMessage::setValue(char *newValue)
        {
        if(value != NULL)
           {
           free(value);
           }
        value=(char *)malloc(sizeof(char)*strlen(newValue));
        strcpy(value, newValue);
        }

      void AKPMessage::setRawMessage(char *newMsg)
        {
        if(rawMessage != NULL)
           {
          // free(rawMessage);
           }
        //rawMessage=(char *)malloc(sizeof(char)*strlen(rawMessage));
        //strcpy(rawMessage, newMsg);
        }
     char *AKPMessage::toAKPString()
        {
        AKPGenerator generator;
        char *retVal;
        
        retVal = generator.getMessage(getTypeAsChar(), name, value);
        
        
        return retVal;
        }
        
        char *AKPMessage::toString()
          {
          int name_sz=strlen(name);
          int value_sz=strlen(value);
          int sz= 27+ name_sz + value_sz;
          char retVal[sz];
          //memset(retVal, 0, sz);
          //retVal[sz-1]='\0';
         // sprintf(retVal, "Type: %s, Name: %s, Value: %s", getTypeAsChar(), name, value);
          
          return retVal;
          }
  void AKPMessage::setValid(int valid)
    {
    validMessage=valid;
    }
          
const char *AKPMessage::getTypeAsChar()
    {
    switch(msgType)
      {
      case ALARM:
        return AKP_ALARM;
      case DATA_STRING:
        return AKP_DATA_STRING;
      case DATA_ANALOG:
        return AKP_DATA_ANALOG;
      case DATA_BOOLEAN:
        return AKP_DATA_BOOLEAN;
      case EVENT:
        return AKP_EVENT;
      case ERROR:
        return AKP_ERROR;
      case COMMAND:
        return AKP_COMMAND;
      case SYSREG:
        return AKP_SYSREG;
      }
      
    return "NONE";  
    }