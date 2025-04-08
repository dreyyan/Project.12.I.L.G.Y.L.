/*----------------------- HEADER FILES -----------------------*/
#pragma once
#include <cstddef>
#include <string>
using namespace std;
/*-------------------- UTILITY PROTOTYPES --------------------*/
// Displays a formatted line within the specified length using the specified symbol
void displayFormat(size_t length, char symbol);

// Displays a formatted line with alternating symbols within the specified length
void displayAlternatingFormat(size_t length, char firstSymbol, char secondSymbol);

// Displays a formatted block within the specified width and height using the specified symbol
void displayBlockFormat(size_t width, size_t height, char symbol);

// Outputs a newline escape sequence 'n' times
void space(size_t n);

// Outputs a delay within 'ms' milliseconds
void delayMs(int ms);

// Outputs a delay within 's' seconds
void delayS(int s);

// Displays the specified string character-by-character every 'ms' milliseconds
void characterDelayAnimation(string stringInput, int ms);

// Prompts the user to press enter to continue with the process
void pressEnter(string process);

// Displays a formatted error message
void displayErrorMessage(const string& errorMessage);

void trim(string& stringInput);

// Converts the specified string to lowercase
void toLowercase(string& stringInput);

// Converts the specified string to uppercase
void toUppercase(string& stringInput);

// Converts the first character of the specified string to uppercase
void capitalize(string& stringInput);

// Navigate the CLI using U/D/R/L values by ANSI escape codes
void moveCursor(int up, int down, int right, int left);

// Navigate the CLI using coordinate(x, y) values by ANSI escape codes
void goTo(int y, int x);

// Clears the console screen
void clearScreen();

// Displays a spinning animation at 'x' for a specified string 
void spinningAnimation(const string& toGenerate, int x);

// Displays a loading bar animation at 'x'
void loadingBarAnimation(int x);