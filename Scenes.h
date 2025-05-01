#ifndef SCENES_H
#define SCENES_H
/*----------------------- HEADER FILES -----------------------*/
/*--------------------- SCENES PROTOTYPES ---------------------*/
void pressEnterToContinue();
// TEXT
inline void displayText1();
inline void displayText2();
inline void displayText3();
inline void displayText4();
inline void displayText5();
inline void displayText6();
inline void displayText7();
// ENTITIES/STRUCTURES
void showClouds();
void hideClouds();
void showLemonadeStand();
void hideLemonadeStand();
void showPlayer();
void hidePlayer();
// MENU
void showStatsMenu();
void showBottomNavigationMenu();
// SCENES
void displayNewGameCutscene();
// GAME FLOW
void displayPreGameTransition();
void goToGameArea();
void startGame();
#endif