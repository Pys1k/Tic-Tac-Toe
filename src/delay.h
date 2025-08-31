#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>
#define SIMULATOR 1


typedef struct {
  unsigned int ENABLE : 1;
  unsigned int TICKINT : 1;
  unsigned int CLCKSOURCE : 1;
  unsigned int unused0 : 13; // -> Flytta 13 bit in.
  unsigned int COUNTFLAG : 1;
  unsigned int : 0; // "align"
  unsigned int LOAD:24, :0;
  unsigned int VAL:24, :0;
} SYSTICK_t;

void delay_250ns(void);
void delay_mikro(uint16_t us);
void delay_milli(uint16_t ms); 

#endif