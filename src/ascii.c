#include <stdio.h>
#include <stdint.h>
#include "ascii.h"

#define SIMULATOR 1

//stulen kod från en labb vi gjorde för varför skriva om det igen?

// Delays
void delay_Xns(unsigned int ns) {
    unsigned int cycles = 1 + (ns * 0.168);  //0.168 aproximation för cykler per ns
    *stk_load = cycles;
    *stk_ctrl = 5;
    while ((*stk_ctrl & 0x10000) == 0);
}
void delay_Xus(unsigned int us) {
    delay_Xns(us * 1000);
}
void delay_Xms(unsigned int ms) {
    delay_Xus(ms * 1000);
}

void ascii_ctrl_bit_set(uint8_t x)
{
  *portOdrLow |= x;
}

void ascii_ctrl_bit_clear(uint8_t x)
{
  *portOdrLow &= ~x;
}

void ascii_write_controller(uint8_t command) {
  delay_Xns(40);
  ascii_ctrl_bit_set(B_E);
  *portOdrHigh = command;
  delay_Xns(230);
  ascii_ctrl_bit_clear(B_E);
  delay_Xns(10);
}

uint8_t ascii_read_controller(void)
{
  ascii_ctrl_bit_set(B_E);
  delay_Xns(360);
  uint8_t rv = *portIdrHigh;
  ascii_ctrl_bit_clear(B_E);
  return rv;
}

void ascii_write_cmd(uint8_t command)
{
  ascii_ctrl_bit_clear(B_RS);
  ascii_ctrl_bit_clear(B_RW);
  ascii_write_controller(command);
}

void ascii_write_data(uint8_t data)
{
  ascii_ctrl_bit_set(B_RS);
  ascii_ctrl_bit_clear(B_RW);
  ascii_write_controller(data);
}

uint8_t ascii_read_status(void)
{
  *portModer &= 0x0000FFFF; // Set b15-b8 as inputs
  ascii_ctrl_bit_clear(B_RS);
  ascii_ctrl_bit_set(B_RW);
  unsigned char rv = ascii_read_controller();
  *portModer |= 0x55550000; // Set b15-b8 as outputs
  return rv;
}

uint8_t ascii_read_data(void)
{
  *portModer |= 0x0000FFFF;
  ascii_ctrl_bit_set(B_RW);
  ascii_ctrl_bit_set(B_RS);
  uint8_t rv = ascii_read_controller();
  *portModer |= 0x55550000;
  return rv;
}

void ascii_clearDisplay(void) {
  while((ascii_read_status() & 0x80) == 0x80) {}
  delay_Xus(8);
  ascii_write_cmd(1);
  delay_Xms(2);
}

void ascii_init(void) {
    ascii_ctrl_bit_set(B_SELECT);
    ascii_write_cmd(0x38);
    delay_Xms(2);
    ascii_write_cmd(0x0C);
    delay_Xms(2);
    ascii_write_cmd(0x01);
    delay_Xms(2);
    ascii_write_cmd(0x06);
    delay_Xms(2);
}

void ascii_write_char(uint8_t c) {
    while (ascii_read_status() & 0x80); 
    delay_Xus(8);
    ascii_write_data(c);
    delay_Xus(43);
}

void ascii_gotoxy(int x, int y) {
    int address = x - 1;
    if (y == 2) address += 0x40;
    ascii_write_cmd(0x80 | address);
}

void init_app() {
  *portModer = 0x55555555;
}


