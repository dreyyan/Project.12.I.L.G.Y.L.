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
void showCustomer1();
void showCustomer2();
void showCustomer3();
void showCustomer4();
void showCustomer5();
void showCustomer6();
void showCustomer7();
void hideCustomer1();
void hideCustomer2();
void hideCustomer3();
void hideCustomer4();
void hideCustomer5();
void hideCustomer6();
void hideCustomer7();

// MENU
void showStatsMenu();
void showBottomNavigationMenu();

// SCENES
void displayNewGameCutscene();

// GAME FLOW
void displayPreGameTransition();
void showCustomer();
void customerGenerator();
void goToGameArea();
void startGame();

#endif