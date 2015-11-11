#ifndef AKPMESSAGECONST_H
#define AKPMESSAGECONST_H

const char cSTX=0x02;
const char cSOH=0x01;
const char cEOT=0x04;
const char cGS=0x1D;
const char cRS=0x1E;
const char cCR=0x0D;
const char cLF=0x0A;

const char AKP_ALARM[5]="ALRM";   //An ALARM,  value should be considered a string
const char AKP_DATA_STRING[5]="DATS"; //Data in a String format
const char AKP_DATA_ANALOG[5]="DATA";  //Data in an numeric format
const char AKP_DATA_BOOLEAN[5]="DATD"; //Data in a boolean/digital format, should be 1 or 0
const char AKP_EVENT[5]="EVNT"; //a generic event, value should be considered string
const char AKP_ERROR[5]="ERRO"; //an error, value should be considered string
const char AKP_COMMAND[5]="CMND"; //a command, value and name can be arbitrary
const char AKP_SYSREG[5]="SYSR"; //a system registration event.


typedef enum { ALARM, DATA_STRING, DATA_ANALOG, DATA_BOOLEAN, EVENT, ERROR, COMMAND, SYSREG } MsgType;
///typedef enum {ANALOG, DIGITAL, STRING} dataType;

#endif