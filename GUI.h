#ifndef GUI_H
#define GUI_H
/*----------------------- HEADER FILES -----------------------*/
#include "Portfolio.h"
/*---------------------- GUI PROTOTYPES ----------------------*/
// GLOBALS
extern int saveFileNum;
extern SaveData currentSaveFile;

void displayHeader();
void createNewGame();

// LOAD/SAVE FILES
void createOrLoad();
void displaySaveFiles();

void displayInformation();
// MENU
void displayContinueMenu();
void displayStartMenu();
void displayExitMenu();
void displayMainMenu();
#endif