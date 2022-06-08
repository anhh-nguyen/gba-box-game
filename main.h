#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// snake game. The snake will be a pink rectangular that move using A,W,S,D key. go to next screen using right arrow. 
// Game end when enough score is gained
// Struct includes heading, score, row, col

#define FRUIT_NUM 10
struct player
{
    int score;
    int row;
    int col;
    int previousRow; //check if this is needed
    int previousColumn; //check if this is needed
};

typedef struct fruit {
    int row;
    int column;
} FRUIT;


void init_fruits(void);
void init_player(void);
void draw_text(void);
int collided(int fruitRow, int fruitColumn);
void bounceChecking(void);

#endif
