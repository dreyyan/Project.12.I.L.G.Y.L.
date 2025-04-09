/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <iomanip>
#include <iostream>
#include "json.hpp" // .json files
#include <string>
#include "Utility.h"
using namespace std;
/*--------------------- GUI DEFINITIONS ----------------------*/
void createNewGame() {
    cout << "creating new game...\n";
}

void displaySaveFiles() {
    string characterName[] = {"Allanah", "Dominique", "Shalyn"};
    int level[] = {1, 2, 3};
    string standName[] = {"Allanah's Lemonan", "Dominique's Lemonan", "Shalyn's Lemonan"};
    int chapter[] = {1, 2, 3};
    int money[] = {0, 500, 1000};

    int saveFile; // To store the save file #

    // Display SAVE #1
    space(1);
    centerText("SAVE #1"); space(1);
    cout << "  " << setw(10) << "Name: " << characterName[0] << '\n';
    cout << "  " << setw(10) << "Stand: " << standName[0] << '\n';
    cout << "  " << setw(10) << "Lvl.: " << level[0] << '\n';
    cout << "  " << setw(10) << "Chapter: " << chapter[0] << '\n';
    cout << "  " << setw(10) << "Money: " << money[0] << " php" << '\n';
    space(1);


    displaySpacedFormat(72, '=');
    space(1);
    centerText("SAVE #2"); space(1);
    cout << "  " << setw(10) << "Name: " << characterName[1] << '\n';
    cout << "  " << setw(10) << "Stand: " << standName[1] << '\n';
    cout << "  " << setw(10) << "Lvl.: " << level[1] << '\n';
    cout << "  " << setw(10) << "Chapter: " << chapter[1] << '\n';
    cout << "  " << setw(10) << "Money: " << money[1] << " php" << '\n';
    space(1);

    displaySpacedFormat(72, '=');
    space(1);
    centerText("SAVE #3"); space(1);
    cout << "  " << setw(10) << "Name: " << characterName[2] << '\n';
    cout << "  " << setw(10) << "Stand: " << standName[2] << '\n';
    cout << "  " << setw(10) << "Lvl.: " << level[2] << '\n';
    cout << "  " << setw(10) << "Chapter: " << chapter[2] << '\n';
    cout << "  " << setw(10) << "Money: " << money[2] << " php" << '\n';

    // Prompt user to select save file
    const int optionCount = 3;
    int x[optionCount] = { 33, 33, 33 };
    int y[optionCount] = { 5, 14, 23 };
    int current = 0;
    char key;
  
    while (true) {
        // Draw all cursors
        for (int i = 0; i < optionCount; ++i) {
            // Draw ">>" at left
            goTo(x[i] - 3, y[i]);
            cout << (i == current ? ">>" : "  ");
    
            // Erase previous "<<" at right if not the current
            if (i != current) {
                if (i == 0) moveCursor(0, 0, 10, 0);
                else if (i == 1) moveCursor(0, 0, 10, 0);
                else if (i == 2) moveCursor(0, 0, 10, 0);
                cout << "  ";
            }
    
            // Draw "<<" at right for current option
            if (i == current) {
                if (current == 0) moveCursor(0, 0, 10, 0);
                else if (current == 1) moveCursor(0, 0, 10, 0);
                else if (current == 2) moveCursor(0, 0, 10, 0);
                cout << "<<";
            }
        }
    
        key = _getch();
        if (key == 72) { // If 'Up Arrow' key is pressed
            current = (current - 1 + optionCount) % optionCount;
        } else if (key == 80) { // If 'Down Arrow' key is pressed
            current = (current + 1) % optionCount;
        } else if (key == 13) { // If 'Enter' key is pressed
            clearScreen();
            break;
        }
    }

    // Navigate to the next screen
    if (current == 0) saveFile = 1;
    else if (current == 1) saveFile = 2;
    else saveFile == 3;

    if (saveFile == 1) {
        createNewGame();
    }
}

void displayHeader() {
    displaySpacedFormat(72, ' ');
    displaySpacedFormat(72, '#');
    displaySpacedFormat(72, ' ');

    cout << "   /$$$$$$     /$$            /$$$$$$      /$$     /$$   /$$"; delayMs(50); space(1);
    cout << "  |_  $$_/    | $$           /$$__  $$    |  $$   /$$/  | $$"; delayMs(50); space(1);
    cout << "    | $$      | $$          | $$  \\__/     \\  $$ /$$/   | $$"; delayMs(50); space(1);
    cout << "    | $$      | $$          | $$ /$$$$      \\  $$$$/    | $$"; delayMs(50); space(1);
    cout << "    | $$      | $$          | $$|_  $$       \\  $$/     | $$"; delayMs(50); space(1);
    cout << "    | $$      | $$          | $$  \\ $$        | $$      | $$"; delayMs(50); space(1);
    cout << "   /$$$$$$ /$$| $$$$$$$$ /$$|  $$$$$$//$$     | $$ /$$  | $$$$$$$$ /$$"; delayMs(50); space(1);
    cout << "  |______/|__/|________/|__/ \\______/|__/     |__/|__/  |________/|__/"; delayMs(50); space(1);

    space(1);
    displaySpacedFormat(72, '#');
}

void displayContinueMenu() {
    displayHeader();
    space(2);

    cout << "Continue";
}

void displayStartMenu() {
    displaySpacedFormat(72, '#');
    centerText("S  E  L  E  C  T    S  A  V  E");
    space(1);
    displaySpacedFormat(72, '#');
    
    displaySaveFiles();
}

void displayExitMenu() {
    exit(0);
}

void displayMainMenu() {
    displayHeader();
    space(2);

    centerText("+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+"); space(1);
    centerText("C   o   n   t   i   n   u   e"); space(1);
    centerText("+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+"); space(1);

    space(2);

    centerText("+-+ +-+ +-+ +-+ +-+"); space(1);
    centerText(" S   t   a   r   t "); space(1);
    centerText("+-+ +-+ +-+ +-+ +-+"); space(1);

    space(2);

    centerText("+-+ +-+ +-+ +-+"); space(1);
    centerText(" E   x   i   t "); space(1);
    centerText("+-+ +-+ +-+ +-+"); space(1);

    // Cursor navigation logic
    const int optionCount = 3;
    int x[optionCount] = { 20, 26, 28 };
    int y[optionCount] = { 17, 22, 27 };
    int current = 0;
    char key;
  
    while (true) {
        // Draw all cursors
        for (int i = 0; i < optionCount; ++i) {
            // Draw ">>" at left
            goTo(x[i] - 3, y[i]);
            cout << (i == current ? ">>" : "  ");
    
            // Erase previous "<<" at right if not the current
            if (i != current) {
                if (i == 0) moveCursor(0, 0, 36, 0);
                else if (i == 1) moveCursor(0, 0, 24, 0);
                else if (i == 2) moveCursor(0, 0, 20, 0);
                cout << "  ";
            }
    
            // Draw "<<" at right for current option
            if (i == current) {
                if (current == 0) moveCursor(0, 0, 36, 0);
                else if (current == 1) moveCursor(0, 0, 24, 0);
                else if (current == 2) moveCursor(0, 0, 20, 0);
                cout << "<<";
            }
        }
    
        key = _getch();
        if (key == 72) { // If 'Up Arrow' key is pressed
            current = (current - 1 + optionCount) % optionCount;
        } else if (key == 80) { // If 'Down Arrow' key is pressed
            current = (current + 1) % optionCount;
        } else if (key == 13) { // If 'Enter' key is pressed
            clearScreen();
            break;
        }
    }

    // Navigate to the next screen
    if (current == 0) displayContinueMenu();
    else if (current == 1) displayStartMenu();
    else displayExitMenu();
}