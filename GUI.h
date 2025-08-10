#ifndef GUI_H
#define GUI_H
/*----------------------- HEADER FILES -----------------------*/
#include <SFML/Audio.hpp>
#include "Portfolio.h"
#include "Station.h"
/*---------------------- GUI PROTOTYPES ----------------------*/

// GLOBALS
extern int saveFileNum;          // Current save file number being used
extern SaveData currentSaveFile; // Current game save file data structure

// Outputs debugging information about the current save file
void debugCurrentSaveFile();
// Displays the game header/title screen
void displayHeader();
// Creates a new game session with default values
void createNewGame();

// LOAD/SAVE FILES
// Presents the option to create a new game or load an existing one
void createOrLoad();
// Displays all available save files
void displaySaveFiles();

// Displays game information
void displayInformation();
// Formats the game time into a readable string
string formatTime(int hour);
// Updates the player's money display
void updateMoney();
// Displays the current game time
void displayTime(int currentHour);
// Updates the game time
void updateTime(int &currentHour);

// MENU
// Continues the current game session
void continueGame();
// Displays the start menu with initial game options
void displayStartMenu();
// Displays the start menu with initial game options
void displayExitMenu();
// Displays the main game menu with all available actions
void displayMainMenu();

#endif