/* ========================================================================== */
/*                                                                            */
/*   AKPParser.c                                                              */
/*   (c) 2013 Chris Meringolo/Axeda                                           */
/*                                                                            */
/*   An implementation of the AKP protocol for Arduino. This class will parse */
/*   strings into AKP objects for easy interaction. It will also validate     */
/*   messages pulled in from the wire                                         */
/*                                                                            */
/* ========================================================================== */

#include "AKPParser.h" 

    AKPParser::AKPParser()
      {
      delimiters[0]=cSTX;
      delimiters[1]=cSOH;
      delimiters[2]=cEOT;
      delimiters[3]=cGS;
      delimiters[4]=cRS;
      delimiters[5]=cCR;
      delimiters[6]=cLF;
      delimiters[7]='\0';
      } 
    
    AKPParser::AKPParser(int debug)
      {
      delimiters[0]=cSTX;
      delimiters[1]=cSOH;
      delimiters[2]=cEOT;
      delimiters[3]=cGS;
      delimiters[4]=cRS;
      delimiters[5]=cCR;
      delimiters[6]=cLF;
      delimiters[7]='\0';
      }

 //AKPMessage AKPParser::parse(char *input)
 AKPMessage *AKPParser::parse(char *input)
        {
        //AKPMessage response;
        if(validate(input))  //parsing will be attempted if and only if the message passes validation
          {
          //AKPMessage response;
          AKPMessage *response;

          response->setType(strtok(input, delimiters));
          response->setName(strtok(NULL, delimiters));
          response->setValue(strtok(NULL, delimiters));
          //response->setRawMessage(input);
          response->setValid(1);
          return response;
          }
        
        return NULL;
        }

int AKPParser::parse(char *input, AKPMessage *dest)
   { 
   int retVal=validate(input);
    if(retVal)  //parsing will be attempted if and only if the message passes validation
          {
          dest->setType(strtok(input, delimiters));
          dest->setName(strtok(NULL, delimiters));
          dest->setValue(strtok(NULL, delimiters));
          //response->setRawMessage(input);
          dest->setValid(1);
          }
    return retVal;
   }
  
 int AKPParser::validate(char *input)
        {
        int chkSTX, chkSOH, chkGS, chkRS, chkEOT, chksz;
        int sz=strlen(input);
        
        
        (sz >= 10) ? chksz=1 : chksz=0;
        (input[0]==cSTX) ? chkSTX=1 : chkSTX=0;
        (input[1]==cSOH) ? chkSOH=1 : chkSOH=0;
        (input[6]==cGS) ? chkGS=1 : chkGS=0;
        
        char *gsLocator = strchr(input, cRS);
        int gsLocation= gsLocator-input+1;
        ((gsLocation > 6)&&(gsLocation < sz)) ? chkRS=1 : chkRS=0;
        
        (input[sz-1]==cEOT) ? chkEOT=1 : chkEOT=0;
        
      /*  Serial.print("chkSTX="); Serial.println(chkSTX);
        Serial.print("chkSOH= ");Serial.println(chkSOH); 
        Serial.print("chkGS= ");Serial.println(chkGS);  
        Serial.print("chkRS= "); Serial.println(chkRS);
        Serial.print("chkEOT= "); Serial.println(chkEOT);
        Serial.print("chksz= "); Serial.println(chksz);     */
        
        return (chkSTX && chkSOH && chkGS && chkRS && chkEOT && chksz);
        //return chkSTX + chkSOH + chkGS + chkRS + chkEOT + chksz;
        }
        
    