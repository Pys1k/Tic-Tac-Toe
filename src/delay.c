
#include "delay.h"
#include <stdio.h>
#include <stdint.h>


volatile SYSTICK_t* SYSTICK2 = (volatile SYSTICK_t*)0xE000E010;

void delay_250ns(void) {
  SYSTICK2->LOAD = 42;
  SYSTICK2->TICKINT = 0;
  SYSTICK2->CLCKSOURCE = 1;
  SYSTICK2->VAL = 0;
  SYSTICK2->ENABLE = 1;
  while(!SYSTICK2->COUNTFLAG) {}
  SYSTICK2->ENABLE = 0;
  return;
}

void delay_mikro(uint16_t us) {
  int i = 0;
  while(i < us * 4) {
    delay_250ns();
    i++;
  }
}

void delay_milli(uint16_t ms) {
#ifdef SIMULATOR
  ms = ms / 1000;
  ms++;
#endif
  delay_mikro(ms * 1000);

}