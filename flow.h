/*----------------------- HEADER FILES -----------------------*/
#pragma once
// Cursor logic
void updateCursor(int y, int x);
void clearArrow(int y, int x);
void hideCursor();
void showCursor();
void resetCursor();

// Screen flows
void continueGame();
void startGame();
void exitGame();

// Choices
void getMenuChoice();

// START
void startFlow();