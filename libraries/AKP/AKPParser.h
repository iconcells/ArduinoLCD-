/* ========================================================================== */
/*                                                                            */
/*   AKPParser.h                                                              */
/*   (c) 2013 Chris Meringolo/Axeda                                           */
/*                                                                            */
/*   An implementation of the AKP protocol for Arduino. This class will parse */
/*   strings into AKP objects for easy interaction. It will also validate     */
/*   messages pulled in from the wire                                         */
/*                                                                            */
/* ========================================================================== */
#ifndef _AKPPARSER_H_
#define _AKPPARSER_H_

#include "AKPMessageConstants.h"
#include "AKPMessage.h"
#include "Arduino.h"

class AKPParser
  {
  public:
    AKPParser();
    AKPParser(int debug);
    AKPMessage *parse(char *input);
    int parse(char *input, AKPMessage *dest);
    int validate(char *input);
    
    char delimiters[8];
  protected:
  
  };


#endif