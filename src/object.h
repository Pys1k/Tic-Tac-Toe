#ifndef OBJECT_H
#define OBJECT_H
#include <stdint.h>
#include <stdbool.h>
#include "graphic.h"

typedef struct {
    circle_t* circle;
    uint8_t accX;
    uint8_t accY;
    uint8_t velX;
    uint8_t velY;
} ball_t;


bool ballToPadCollision(ball_t* ball, rectangle_t rect);

#endif