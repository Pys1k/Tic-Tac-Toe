
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <stdint.h>

 
extern uint32_t display[64][128];

 
typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t w;
    uint8_t h;
} rectangle_t;

typedef struct {
    uint8_t x0;
    uint8_t y0;
    uint8_t x1;
    uint8_t y1;
} line_t;

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t r;
} circle_t;

 
void graphic_initalize(void);
void graphic_clear_screen(void);
void graphic_pixel_set(int x, int y);
void graphic_pixel_clear(int x, int y);

 
void draw_line(line_t *line);
void draw_rectangle(rectangle_t *rect);
void draw_circle(circle_t *circle);

void clear_display();
void update_display(uint32_t display[64][128]);


#endif