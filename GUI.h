#ifndef GUI_H
#define GUI_H
/*----------------------- HEADER FILES -----------------------*/
#include "Portfolio.h"
#include "Station.h"
/*---------------------- GUI PROTOTYPES ----------------------*/
// GLOBALS
extern int saveFileNum;
extern SaveData currentSaveFile;

void debugCurrentSaveFile();
void displayHeader();
void createNewGame();

// LOAD/SAVE FILES
void createOrLoad();
void displaySaveFiles();

void displayInformation();
string formatTime(int hour);
void displayTime(int currentHour);
void updateTime(int &currentHour);
// MENU
void continueGame();
void displayStartMenu();
void displayExitMenu();
void displayMainMenu();
#endif