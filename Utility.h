#ifndef UTILITY_H
#define UTILITY_H
/*----------------------- HEADER FILES -----------------------*/
#include <cstddef>
#include <string>
// .json
#include "json.hpp"
#include "Portfolio.h"
using json = nlohmann::json;
using namespace std;
/*-------------------- UTILITY PROTOTYPES --------------------*/
// Displays a formatted line within the specified length using the specified symbol
void displayFormat(size_t length, char symbol);

// Displays a formatted line within the specified length using the specified symbol /w newline character
void displaySpacedFormat(size_t length, char symbol);

// Displays a formatted line with alternating symbols within the specified length
void displayAlternatingFormat(size_t length, char firstSymbol, char secondSymbol);

// Displays a formatted block within the specified width and height using the specified symbol
void displayBlockFormat(size_t width, size_t height, char symbol);

// Displays a formatted block within the specified width and height using the specified symbol /w newline character
void displayBlockSpacedFormat(size_t width, size_t height, char symbol);

void displayBorder(size_t height, char symbol);

void displayHLine(int x, int y, size_t length, char symbol);

void displayVLine(int x, int y, size_t length, char symbol);

// Outputs a newline escape sequence 'n' times
void space(size_t n);

// Outputs a delay within 'ms' milliseconds
void delayMs(int ms);

// Outputs a delay within 's' seconds
void delayS(int s);

// Displays the specified string character-by-character every 'ms' milliseconds
void characterDelayAnimation(string stringInput, int ms);

// Displays the specified string line-by-line every 'ms' milliseconds
void lineDelayAnimation(string stringInput, int ms);

// Prompts the user to press enter to continue with the process
void pressEnter(string process);

// Trim whitespaces at the front and end of the string
void trim(string& stringInput);

// Converts the specified string to lowercase
void toLowercase(string& stringInput);

// Converts the specified string to uppercase
void toUppercase(string& stringInput);

// Converts the first character of the specified string to uppercase
void capitalize(string& stringInput);

// Clears the console screen
void clearScreen();

// Displays a spinning animation at 'x' for a specified string 
void spinningAnimation(const string& toGenerate, int x);

// Displays a loading bar animation at 'x'
void loadingBarAnimation(int x);

// Centers the specified text in the console
void centerText(string textInput);

// Hide blinking cursor
void hideCursor();

// Show blinking cursor
void showCursor();

// Navigate the CLI using U/D/R/L values by ANSI escape codes
void moveCursor(int up, int down, int right, int left);

// Navigate the CLI using coordinate(x, y) values by ANSI escape codes
void goTo(int y, int x);

SaveData loadSaveData(int saveFileNum, const string& filename);

#endif