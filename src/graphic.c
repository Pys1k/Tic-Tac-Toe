
#include "graphic.h"
#include <stdlib.h>

__attribute__((naked))
void graphic_initalize(void) {
    __asm volatile (" .HWORD 0xDFF0\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_clear_screen(void) {
    __asm volatile (" .HWORD 0xDFF1\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_set(int x, int y) { 
    __asm volatile (" .HWORD 0xDFF2\n");
    __asm volatile (" BX LR\n");
}

__attribute__((naked))
void graphic_pixel_clear(int x, int y) {
    __asm volatile (" .HWORD 0xDFF3\n");
    __asm volatile (" BX LR\n");
}

void update_display(uint32_t display[64][128]) {
    for (int y = 0; y < 64; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            if(display[y][x] == 0) {
                graphic_pixel_clear(x+1, y+1);
            
            } else {
                graphic_pixel_set(x+1, y+1);
                
            }
        }
        
    }
    
}

void draw_line(line_t *line) {
    int x0 = line->x0, y0 = line->y0, x1 = line->x1, y1 = line->y1;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        if (x0 >= 0 && x0 < 128 && y0 >= 0 && y0 < 64) { // Bounds check
            graphic_pixel_set(x0, y0);  // Actually draw on the display
        }

        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}


void draw_rectangle(rectangle_t *rect) {
    line_t top = {rect->x, rect->y, rect->x + rect->w - 1, rect->y};         // Top edge
    line_t bottom = {rect->x, rect->y + rect->h - 1, rect->x + rect->w - 1, rect->y + rect->h - 1}; // Bottom edge
    line_t left = {rect->x, rect->y, rect->x, rect->y + rect->h - 1};         // Left edge
    line_t right = {rect->x + rect->w - 1, rect->y, rect->x + rect->w - 1, rect->y + rect->h - 1}; // Right edge

    draw_line(&top);
    draw_line(&bottom);
    draw_line(&left);
    draw_line(&right);
}

void draw_circle(circle_t *circle) {
    int x0 = circle->x;  // Center of the circle (x-coordinate)
    int y0 = circle->y;  // Center of the circle (y-coordinate)
    int r = circle->r;    // Radius of the circle
    int x = r, y = 0;     // Start at the circle's rightmost point
    int p = 1 - r;        // Initial decision parameter

    while (x >= y) {
        // Draw 8 symmetrical points (with boundary checks) based on the center (x0, y0)
        
        // Right and top
        if (x0 + x < 128 && y0 + y < 64) graphic_pixel_set(x0 + x, y0 + y);  
        // Left and top
        if (x0 - x >= 0 && y0 + y < 64) graphic_pixel_set(x0 - x, y0 + y);  
        // Right and bottom
        if (x0 + x < 128 && y0 - y >= 0) graphic_pixel_set(x0 + x, y0 - y);  
        // Left and bottom
        if (x0 - x >= 0 && y0 - y >= 0) graphic_pixel_set(x0 - x, y0 - y);  
        
        // Right and top-right
        if (x0 + y < 128 && y0 + x < 64) graphic_pixel_set(x0 + y, y0 + x);  
        // Left and top-right
        if (x0 - y >= 0 && y0 + x < 64) graphic_pixel_set(x0 - y, y0 + x);  
        // Right and bottom-right
        if (x0 + y < 128 && y0 - x >= 0) graphic_pixel_set(x0 + y, y0 - x);  
        // Left and bottom-right
        if (x0 - y >= 0 && y0 - x >= 0) graphic_pixel_set(x0 - y, y0 - x);  

        y++;  // Increment y-coordinate

        // Update the decision parameter
        if (p <= 0) {
            p += 2 * y + 1;
        } else {
            x--;  // Move left along the x-axis
            p += 2 * (y - x) + 1;
        }
    }
}



void clear_display() {
    graphic_clear_screen();
}
