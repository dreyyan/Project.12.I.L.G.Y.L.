#ifndef GUI_H
#define GUI_H
/*----------------------- HEADER FILES -----------------------*/
#include "Portfolio.h"
/*---------------------- GUI PROTOTYPES ----------------------*/
extern int saveFileNum;
extern SaveData currentSaveFile;
void displayHeader();
void playCutscene1();
void createNewGame();

void createOrLoad();
void displaySaveFiles();

void displayInformation();
// MENU
void displayContinueMenu();
void displayStartMenu();
void displayExitMenu();
void displayMainMenu();
#endif