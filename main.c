#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gba.h"
#include "images/gameOver.h"
#include "images/startGame.h"
#include "images/pinkBlock.h"
#include "images/winGame.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  BETWEEN,
  PLAY,
  WIN,
  OVER
};

FRUIT *pointer;
FRUIT fruits[FRUIT_NUM];
struct player PLAYER;
long i;

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw


    switch (state) {
      case START:
        waitForVBlank();
        drawFullScreenImageDMA(startGame);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          waitForVBlank();
          drawRectDMA(0,0,240,160, WHITE);
          init_player();

          init_fruits();

          draw_text();
          i = 0;
          pointer = &fruits[i];
          state = PLAY;
          }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons,previousButtons)) {
          state = OVER;
        }
        break;
      case BETWEEN:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons,previousButtons)) {
          state = START;
        }
        if (PLAYER.score == 9) {
          state = WIN;
        } else {
          i = i + 1;
          *pointer = pointer[i];
          PLAYER.score = PLAYER.score + 1;
          waitForVBlank();
          draw_text();
          drawImageDMA(pointer->row, pointer->column, 20, 20, pinkBlock);
          state = PLAY;
        }
      break;
      case PLAY:
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons,previousButtons)) {
          state = START;
        }
          // if collide increament score and load a new location for pink box
          // not collide, the box can keep going
        if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {
          PLAYER.previousRow = PLAYER.row;
          PLAYER.previousColumn = PLAYER.col;
          PLAYER.row = PLAYER.row - 10;
          bounceChecking();
          waitForVBlank();
          drawRectDMA(PLAYER.previousRow, PLAYER.previousColumn, 20, 20, WHITE);
          drawRectDMA(PLAYER.row, PLAYER.col, 20, 20, MAGENTA);
          if (collided(pointer->row, pointer->column)) {
            state = BETWEEN;
          }
        }
        if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {
          PLAYER.previousRow = PLAYER.row;
          PLAYER.previousColumn = PLAYER.col;
          PLAYER.row = PLAYER.row + 10;
          bounceChecking();
          waitForVBlank();
          drawRectDMA(PLAYER.previousRow, PLAYER.previousColumn, 20, 20, WHITE);
          drawRectDMA(PLAYER.row, PLAYER.col, 20, 20, MAGENTA);
          if (collided(pointer->row, pointer->column)) {
            state = BETWEEN;
          }
        }
        if (KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {
          PLAYER.previousColumn = PLAYER.col;
          PLAYER.previousRow = PLAYER.row;
          PLAYER.col = PLAYER.col - 10;
          bounceChecking();
          waitForVBlank();
          drawRectDMA(PLAYER.previousRow, PLAYER.previousColumn, 20, 20, WHITE);
          drawRectDMA(PLAYER.row, PLAYER.col, 20, 20, MAGENTA);
          if (collided(pointer->row, pointer->column)) {
            state = BETWEEN;
          }
        }
        if (KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons,previousButtons)) {
          PLAYER.previousColumn = PLAYER.col;
          PLAYER.previousRow = PLAYER.row;
          PLAYER.col = PLAYER.col + 10;
          bounceChecking();
          waitForVBlank();
          drawRectDMA(PLAYER.previousRow, PLAYER.previousColumn, 20, 20, WHITE);
          drawRectDMA(PLAYER.row, PLAYER.col, 20, 20, MAGENTA);
          if (collided(pointer->row, pointer->column)) {
            state = BETWEEN;
          }
        }
        break;
      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(winGame);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = START;
        }
      break;
      case OVER:
        waitForVBlank();
        drawFullScreenImageDMA(gameOver);
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = START;
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used
  return 0;
}


int collided(int fruitRow, int fruitColumn) {
  if (fruitRow == PLAYER.row && fruitColumn == PLAYER.col) {
    return 1;
  }
  return 0;
}

void init_fruits(void) {
    FRUIT *fruit = &fruits[0];
    fruit->row = 120;
    fruit->column = 30;
    fruit = &fruits[1];
    fruit->row = 30;
    fruit->column = 120;

    fruit = &fruits[2];
    fruit->row = 70;
    fruit->column = 60;

    fruit = &fruits[3];
    fruit->row = 80;
    fruit->column = 120;

    fruit = &fruits[4];
    fruit->row = 120;
    fruit->column = 40;

    fruit = &fruits[5];
    fruit->row = 30;
    fruit->column = 150;

    fruit = &fruits[6];
    fruit->row = 130;
    fruit->column = 120;

    
    fruit = &fruits[7];
    fruit->row = 130;
    fruit->column = 30;

    fruit = &fruits[8];
    fruit->row = 60;
    fruit->column = 100;

    fruit = &fruits[9];
    fruit->row = 90;
    fruit->column = 120;

    fruit = &fruits[0];
    waitForVBlank();
    drawImageDMA(fruit->row, fruit->column, 20, 20, pinkBlock);
}

void init_player(void) {
    PLAYER.score = 0;
    PLAYER.col = 10;
    PLAYER.row = 10;
    PLAYER.previousColumn = 10;
    PLAYER.previousRow = 10;
    waitForVBlank();
    drawRectDMA(PLAYER.row, PLAYER.col, 20, 20, MAGENTA);
}

void draw_text(void) {
  drawRectDMA(152, 42, 6, 8, WHITE);
  drawChar(152, 0, 'S', MAGENTA);
  drawChar(152, 7, 'C', MAGENTA);
  drawChar(152, 14, 'O', MAGENTA);
  drawChar(152, 21,'R', MAGENTA);
  drawChar(152, 28, 'E', MAGENTA);
  drawChar(152, 35, ':', MAGENTA);
  char charScore[12];
  sprintf(charScore, "%d", PLAYER.score);
  drawChar(152, 42, *charScore, MAGENTA);
}

void bounceChecking(void) {
  if (PLAYER.row > 130) {
    PLAYER.row = 130;
  }
  if (PLAYER.col > 220) {
    PLAYER.col = 220;
  }
  if (PLAYER.col < 0 ) {
    PLAYER.col = 0;
  }
  if (PLAYER.row < 0 ) {
    PLAYER.row = 0;
  }
}


