

#include "object.h"

 
bool ballToPadCollision(ball_t* ball, rectangle_t rect) {

    bool horizontalCollision = (ball->circle->x + ball->circle->r > rect.x) && 
                               (ball->circle->x - ball->circle->r < rect.x + rect.w);
    

    bool verticalCollision = (ball->circle->y + ball->circle->r > rect.y) &&
                             (ball->circle->y - ball->circle->r < rect.y + rect.h);


    if (horizontalCollision && verticalCollision) {
        return true;  
    }

    return false;  
}

