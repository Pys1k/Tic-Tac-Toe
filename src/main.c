#include "graphic.h"         
#include "input.h"         
#include "delay.h"     
#include "ascii.h" 
#include <stdbool.h>        
#include <stdint.h>          
#include <string.h>          

#define BOARD_SIZE 3
#define CELL_SIZE 20
#define CIRCLE_R = 8

uint8_t board[BOARD_SIZE][BOARD_SIZE] = {0};   // 0 = tomm, 1 = X, 2 = O
bool x_turn = true;                             // sann om det är X tur annars false
bool game_over = false;                        // self-explanatory
uint16_t pressedKeys = 0;


bool check_win_condition() {
    // rows
    for (int r = 0; r < BOARD_SIZE; r++) {
        if (board[r][0] != 0 && board[r][0] == board[r][1] && board[r][1] == board[r][2])
            return true;
    }
    //  columns
    for (int c = 0; c < BOARD_SIZE; c++) {
        if (board[0][c] != 0 && board[0][c] == board[1][c] && board[1][c] == board[2][c])
            return true;
    }
    //  diagonals
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

//är den full?
bool check_draw_condition() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (board[r][c] == 0)  //här är den tomm, inte draw 
                return false;
        }
    }
    return true;  //draw!
}

int main(void) {
    init_keyb();
    init_GPIO_D_PINS();
    graphic_initalize();

    // ascii display busgrajor
    init_app();
    ascii_init();
    ascii_gotoxy(1,1);

    char *s;
    char test1[] = "Välkommen! ";
    char test2[] = "X börjar";

    s = test1;
    while (*s)
      ascii_write_char(*s++);
    ascii_gotoxy(1,2);
    s = test2;
    while (*s)
      ascii_write_char(*s++);

    int x0 = 33, y0 = 1;    //top vänstra av brädet
    int cell = CELL_SIZE;    // storleken på var box

    while (1) {
        clear_display();   

        if (!game_over) {
            if ((pressedKeys & (1 << KEY_1)) && board[0][0] == 0) {
                board[0][0] = x_turn ? 1 : 2;  // placera X (1) eller O (2)
                x_turn = !x_turn;              // nu är det den andras tur!
            } else if ((pressedKeys & (1 << KEY_2)) && board[0][1] == 0) {
                board[0][1] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_3)) && board[0][2] == 0) {
                board[0][2] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_4)) && board[1][0] == 0) {
                board[1][0] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_5)) && board[1][1] == 0) {
                board[1][1] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_6)) && board[1][2] == 0) {
                board[1][2] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_7)) && board[2][0] == 0) {
                board[2][0] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_8)) && board[2][1] == 0) {
                board[2][1] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            } else if ((pressedKeys & (1 << KEY_9)) && board[2][2] == 0) {
                board[2][2] = x_turn ? 1 : 2;
                x_turn = !x_turn;
            }
        } else {
            // Game over
            if (pressedKeys & (1 << KEY_D)) {
                memset(board, 0, sizeof(board));  // ränsa
                game_over = false;
                x_turn = true;
            }
        }

        if (check_win_condition()) {
            game_over = true;
        } else if (check_draw_condition()) {
            game_over = true;
        }

        // här ritas själva brädet, dynamisk storlek såklart ;)
        line_t v1 = { x0 + cell, y0, x0 + cell, y0 + 3 * cell };
        line_t v2 = { x0 + 2 * cell, y0, x0 + 2 * cell, y0 + 3 * cell };
        line_t h1 = { x0, y0 + cell, x0 + 3 * cell, y0 + cell };
        line_t h2 = { x0, y0 + 2 * cell, x0 + 3 * cell, y0 + 2 * cell };
        draw_line(&v1);  
        draw_line(&v2);
        draw_line(&h1);
        draw_line(&h2);

        // behandlar logiken att rita x och O 
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                int cx0 = x0 + c * cell;
                int cy0 = y0 + r * cell;
                int cx1 = cx0 + cell - 1;
                int cy1 = cy0 + cell - 1;

                if (board[r][c] == 1) {
                    // X
                    line_t d1 = { cx0 + 2, cy0 + 2, cx1 - 2, cy1 - 2 };
                    line_t d2 = { cx1 - 2, cy0 + 2, cx0 + 2, cy1 - 2 };
                    draw_line(&d1);
                    draw_line(&d2);
                } else if (board[r][c] == 2) {
                    // O
                    uint8_t centerX = cx0 + cell / 2;
                    uint8_t centerY = cy0 + cell / 2;
                    circle_t circ = { centerX, centerY, CIRCLE_R };  //8 i radie
                    draw_circle(&circ);
                }
            }
        }

        delay_mikro(50);  
    }
}
