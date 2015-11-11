/* ========================================================================== */
/*                                                                            */
/*   AKPGenerator.cpp                                                               */
/*   (c) 2013 Chris Meringolo/Axeda                                           */
/*                                                                            */
/*   An implementation of the AKP protocol for Arduino. This class will create*/
/*   string representations of AKP messages based on AKP message objects OR   */
/*   on the fly by method calls                                               */
/* ========================================================================== */
#include "AKPGenerator.h"
#include "AKPMessageConstants.h"

  AKPGenerator::AKPGenerator()
    {
    debug=0;
    }
  AKPGenerator::AKPGenerator(int debug)
    {
    debug=debug;
    }


char* AKPGenerator::getMessage(const char* type, String name, String value)
  {
  int name_sz=name.length()+1;
  int value_sz=value.length()+1;
  int sz = 10 + name_sz + value_sz;
//  Serial.println(sz);
  char retVal[sz];
  memset(retVal, 0, sz);
  //retVal[sz]='\0';
  char chr_name[name_sz];
  char chr_value[value_sz];

  name.toCharArray(chr_name, name_sz);
  value.toCharArray(chr_value, value_sz);

//   Serial.print(chr_name); Serial.println("|");
//   Serial.print(chr_value); Serial.println("|");
  int cursor=0;
  retVal[cursor]= cSTX;
  cursor++;   //1
  retVal[cursor]= cSOH;
  cursor++;    //2
  strcat(retVal, type);
  cursor+=4;   //6
  retVal[cursor] = cGS;
  cursor++;
  strncat(retVal+cursor, chr_name, name_sz-1);
  cursor+=name_sz-1; 
  retVal[cursor] = cRS;
  cursor++;
  strncat(retVal+cursor, chr_value, value_sz-1);
  cursor+=value_sz-1;
  
  retVal[cursor] = cEOT;
  cursor++;

  return retVal;
  }

   //======================GENERATOR METHODS======================
    char* AKPGenerator::AKP_getErrorMessage(String value)
      {
      return getMessage(AKP_ERROR, "sys", value);
      }
    char* AKPGenerator::AKP_getEventMessage(String name, String value)
      {
      return getMessage(AKP_EVENT, name, value);
      }
    char* AKPGenerator::AKP_getAlarmMessage(String name, String value)
      {
      return getMessage(AKP_ALARM, name, value);
      }
    char* AKPGenerator::AKP_getDataMessage(String name, String value)
      {
       return getMessage(AKP_DATA_STRING, name, value);
      }
    char* AKPGenerator::AKP_getDataMessage(String name, long value)
      {
       return getMessage(AKP_DATA_ANALOG, name, String(value, DEC));
      }
    char* AKPGenerator::AKP_getDataMessage(String name, boolean value)
      {
       if(value == true)
       return getMessage(AKP_DATA_BOOLEAN, name, "true");

       return getMessage(AKP_DATA_BOOLEAN, name, "false");
      }
    char* AKPGenerator::AKP_getCommandMessage(String command)
      {
      return getMessage(AKP_COMMAND, "cmd", command);
      }


