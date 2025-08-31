#include "input.h"
#include <stdio.h>

GPIO * GPIO_D = (GPIO *)0x40020C00;
unsigned int keybChar[4][4] = {
    {KEY_1, KEY_2, KEY_3, KEY_A},  
    {KEY_4, KEY_5, KEY_6, KEY_B},  
    {KEY_7, KEY_8, KEY_9, KEY_C}, 
    {KEY_STAR, KEY_0, KEY_HASH, KEY_D}  
};

unsigned char noInput = 0;

void activateRow(unsigned int row) {
    GPIO_D->ODR_HIGH = (0x10 << row);
}

unsigned int getColumn() {
    unsigned int res = GPIO_D->IDR_HIGH;
    switch(res &= -res) {
        case 1:
            return 1; 
        case 2:
            return 2; 
        case 4:
            return 3; 
        case 8:
            return 4; 
        case 0: 
            return 0;
    }
    return -1;
}

void handler1() {
    uint16_t newKeys = getKey();
    if (newKeys == 0x0) {
        pressedKeys = 0;
    } else {
        pressedKeys |= newKeys;
        uint16_t releasedKeys = pressedKeys & ~newKeys;
        if (releasedKeys != 0) {
            pressedKeys &= ~releasedKeys;
        }
    }
}

void init_GPIO_D_PINS() {
    *(((void (**)(void))(0x2001C000 + 0xE0 ))) = &handler1;
    *(((void (**)(void))(0x2001C000 + 0x9C ))) = &handler1;
    *SYSCFG_EXTICR3 &= ~0xFFFF;
    *SYSCFG_EXTICR3 |= 0x3333;
    *EXTI_IMR |= 0xF00;
    *EXTI_RTSR |= 0xF00;
    *EXTI_FTSR |= 0xF00;
    *EXTI_PR |= 0xF00;
    *NVIC_ISER0 |= (1 << 23);
    *NVIC_ISER1 |= (1 << 8);
}

void init_keyb() {
    GPIO_D->MODE = 0x55005555;
    GPIO_D->PUPD = 0x00AA0000;
    GPIO_D->OTYPE = 0x0;
    GPIO_D->SPEED = 0x0;
    GPIO_D->ODR_LOW = 0;
    GPIO_D->ODR_HIGH = 0xF0;
}

bool isKeyPressed(input_key_t key, uint16_t keys) {
    unsigned char pressedKeys = keys;
    return (pressedKeys & (1 << key));
}

unsigned short getKey() {
    *EXTI_IMR = 0x0;
    unsigned short result = 0;
    noInput = 0;

    for (int row = 0; row < 4; row++) {
        activateRow(row);
        unsigned int column = getColumn();
        
        if (column != 0) {  
            noInput = 1;
            if (column == 1) result |= (1 << keybChar[row][0]);
            if (column == 2) result |= (1 << keybChar[row][1]);
            if (column == 3) result |= (1 << keybChar[row][2]);
            if (column == 4) result |= (1 << keybChar[row][3]);
        }
    }

    GPIO_D->ODR_HIGH = 0xF0;
    *EXTI_PR |= 0xF00;
    *EXTI_IMR = 0xF00;
    
    return result;
}
