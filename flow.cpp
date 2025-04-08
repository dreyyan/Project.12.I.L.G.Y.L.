/*----------------------- HEADER FILES -----------------------*/
#include <algorithm>
#include <iostream>
#include <chrono>
#include <conio.h> // _getch()
#include <string>
#include <thread>
#include <vector>
#include "GUI.h"
#include "Utility.h"
using namespace std;
// Create instance
GUI gui;

/*----------------------- CURSOR LOGIC -----------------------*/
void updateCursor(int y, int x) {
    cout << "\033[" << y << ";" << x << "H" << ">>";
}

void clearArrow(int y, int x) {
    cout << "\033[" << y << ";" << x << "H" << "  ";
}

void hideCursor() {
    cout << "\033[?25l";
}

void showCursor() {
    cout << "\033[?25h";
}

void resetCursor() {
    goTo(1, 1);
}

/*--------------------- FLOW DEFINITIONS ---------------------*/
void continueGame() {
    gui.displayContinueMenu();
}

void startGame() {
    gui.displayStartMenu();
}

void exitGame() {
    exit(0);
}

/*------------------- CHOICES DEFINITIONS --------------------*/
void getMenuChoice() {
    int positionsY[] = {21, 31, 41}; // Y-coordinates
    int positionsX[] = {39, 48, 51}; // X-coordinates

    // 0 - Continue, 1 - Start, 2 - Exit
    int selected = 0;
    int options = 3;

    // Initially show arrow at first option
    updateCursor(positionsY[selected], positionsX[selected]);

    while (true) {
        int ch = _getch();

        if (ch == 224) { // Prefix for "Arrow Key"
            int arrow = _getch();

            // Clear the arrow
            clearArrow(positionsY[selected], positionsX[selected]);

            if (arrow == 72) { // Up
                selected = (selected - 1 + options) % options;
            } else if (arrow == 80) { // Down
                selected = (selected + 1) % options;
            }

            updateCursor(positionsY[selected], positionsX[selected]);
        } else if (ch == 13) { // Enter
            break;
        }
    }

    // Clear the console screen & reset cursor before moving to the next screen
    clearScreen();
    resetCursor();

    // Navigate according to selected option
    switch (selected) {
        case 0: continueGame(); break;
        case 1: startGame(); break;
        case 2: exitGame(); break;
        default: cout << "ERROR: Invalid selection\n"; break;
    }
}

void startFlow() {
    hideCursor();

    // 1. Display "Start_Menu"
    gui.displayMenu();
    // 2. Get "Start_Menu" choice
    getMenuChoice();
    cin.get();
}