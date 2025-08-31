#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stdbool.h>

#define GPIO_D_BASE 0x40020C00
#define SCB_VTOR (volatile unsigned int *)0xE000ED08
#define SYSCFG_EXTICR1 (volatile unsigned int *)0x40013808
#define SYSCFG_EXTICR2 (volatile unsigned int *)0x4001380C
#define EXTI_IMR (volatile unsigned int *)0x40013C00
#define EXTI_RTSR (volatile unsigned int *)0x40013C08
#define EXTI_FTSR (volatile unsigned int *)0x40013C0C
#define EXTI_PR (volatile unsigned int *)0x40013C14
#define NVIC_ISER0 (volatile unsigned int *)0xE000E100
#define SYSCFG_EXTICR3 (volatile unsigned int *)0x40013810
#define NVIC_ISER1 (volatile unsigned int *)0xE000E104

extern uint16_t pressedKeys;

typedef struct {
    unsigned int MODE;
    unsigned short OTYPE;
    unsigned int SPEED;
    unsigned int PUPD;
    unsigned char IDR_LOW;
    unsigned char IDR_HIGH;
    unsigned short unused0;
    unsigned char ODR_LOW;
    unsigned char ODR_HIGH;
} GPIO;

typedef enum {
    KEY_1 = 0, KEY_2, KEY_3, KEY_A,
    KEY_4, KEY_5, KEY_6, KEY_B,
    KEY_7, KEY_8, KEY_9, KEY_C,
    KEY_STAR, KEY_0, KEY_HASH, KEY_D
} input_key_t;


void init_GPIO_D_PINS();
void handler();
void init_keyb();
bool isKeyPressed(input_key_t key, uint16_t keys);
uint16_t getKey();

#endif