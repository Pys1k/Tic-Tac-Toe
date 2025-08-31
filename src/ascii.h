#ifndef YOUR_HEADER_H
#define YOUR_HEADER_H

#include <stdint.h>

// Pin configuration addresses
#define PORT_BASE 0x40021000
#define portModer    ((volatile unsigned int *) (PORT_BASE + 0))
#define portOtyper   ((volatile unsigned short *) (PORT_BASE + 4))
#define portOspeedr ((volatile unsigned int *) (PORT_BASE + 8))
#define portPupdr   ((volatile unsigned int *) (PORT_BASE + 0xC))

// IO addresses
#define portIdrLow   ((volatile unsigned char *) (PORT_BASE + 0x10))
#define portIdrHigh  ((volatile unsigned char *) (PORT_BASE + 0x11))
#define portOdrLow   ((volatile unsigned char *) (PORT_BASE + 0x14))
#define portOdrHigh  ((volatile unsigned char *) (PORT_BASE + 0x15))

// Control register bits
#define B_E       0x40    // Bit 6
#define B_SELECT  4      // Bit 2
#define B_RW      2      // Bit 1
#define B_RS      1      // Bit 0 

// SysTick addresses
#define STK_BASE 0xE000E010
#define stk_ctrl  ((volatile unsigned int *)(STK_BASE + 0))
#define stk_load  ((volatile unsigned int *)(STK_BASE + 0x4))
#define stk_val   ((volatile unsigned int *)(STK_BASE + 0x8))
#define stk_calib ((volatile unsigned int *)(STK_BASE + 0xC))

// Function prototypes
void delay_Xns(unsigned int ns);
void delay_Xus(unsigned int us);
void delay_Xms(unsigned int ms);
void ascii_ctrl_bit_set(uint8_t x);
void ascii_ctrl_bit_clear(uint8_t x);
void ascii_write_controller(uint8_t command);
uint8_t ascii_read_controller(void);
void ascii_write_cmd(uint8_t command);
void ascii_write_data(uint8_t data);
uint8_t ascii_read_status(void);
uint8_t ascii_read_data(void);
void ascii_clearDisplay(void);
void ascii_init(void);
void ascii_write_char(uint8_t c);
void ascii_gotoxy(int x, int y);
void init_app(void);

#endif // YOUR_HEADER_H
