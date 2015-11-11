/* ========================================================================== */
/*                                                                            */
/*   AKPGenerator.h                                                           */
/*   (c) 2013 Chris Meringolo/Axeda                                           */
/*                                                                            */
/*   An implementation of the AKP protocol for Arduino. This class will create*/
/*   string representations of AKP messages based on AKP message objects OR   */
/*   on the fly by method calls                                               */
/* ========================================================================== */

#ifndef _AKPGENERATOR_H_
#define _AKPGENERATOR_H_

#include "Arduino.h"


class AKPGenerator
  {
  public:
     AKPGenerator();
     AKPGenerator(int debug);
      //AKPMessage generation Methods
    char* AKP_getErrorMessage(String value);
    char* AKP_getEventMessage(String name, String value);
    char* AKP_getAlarmMessage(String name, String value);
    char* AKP_getDataMessage(String name, String value);
    char* AKP_getDataMessage(String name, long value);
    char* AKP_getDataMessage(String name, boolean value);
    char* AKP_getCommandMessage(String command);
 
    int debug;
    char* getMessage(const char* type, String name, String value);
     private:
  };


#endif