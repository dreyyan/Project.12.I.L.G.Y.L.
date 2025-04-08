/*----------------------- HEADER FILES -----------------------*/
#include <iostream>
#include "GUI.h"
#include "Utility.h"
using namespace std;
// Default Constructor
GUI::GUI() {}

void GUI::displayTitleHeader() const {
    displayBlockFormat(132, 2, '#');
    space(2);

    // Width: 132
    cout << "     ___   __   _      ___   __          ____  _                   __   __              _                                         \n";
    delayMs(100);
    cout << "    |_ _| / _| | |    |_ _| / _|  ___   / ___|(_)__   __ ___  ___  \\ \\ / /___   _   _  | |     ___  _ __ ___    ___   _ __   ___ \n";
    delayMs(100);
    cout << "     | | | |_  | |     | | | |_  / _ \\ | |  _ | |\\ \\ / // _ \\/ __|  \\ V // _ \\ | | | | | |    / _ \\| '_ ` _ \\  / _ \\ | '_ \\ / __|\n";
    delayMs(100);
    cout << "     | | |  _| | |___  | | |  _||  __/ | |_| || | \\ V /|  __/\\__ \\   | || (_) || |_| | | |___|  __/| | | | | || (_) || | | |\\__ \\\n";
    delayMs(100);
    cout << "    |___||_|   |_____||___||_|   \\___|  \\____||_|  \\_/  \\___||___/   |_| \\___/  \\__,_| |_____|\\___||_| |_| |_| \\___/ |_| |_||___/\n";
    delayMs(100);
}

void GUI::displayContinueText() const {
    int center = 44;
    moveCursor(0, 0, center, 0);
    cout << "                                                 \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << " _____ _____ _____ _____ _____ _____ _____ _____ \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|     |     |   | |_   _|     |   | |  |  |   __|\n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|   --|  |  | | | | | | |-   -| | | |  |  |   __|\n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|_____|_____|_|___| |_| |_____|_|___|_____|_____|\n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "                                                 \n";
    delayMs(100);
}

void GUI::displayStartText() const {
    int center = 53;
    moveCursor(0, 0, center, 0);
    cout << " _____ _____ _____ _____ _____ \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|   __|_   _|  _  | __  |_   _|\n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|__   | | | |     |    -| | |  \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|_____| |_| |__|__|__|__| |_|  \n";
    delayMs(100);
}

void GUI::displayExitText() const {
    int center = 56;
    moveCursor(0, 0, center, 0);
    cout << " _____ __ __ _____ _____ \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|   __|  |  |     |_   _|\n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|   __|-   -|-   -| | |  \n";
    delayMs(100);
    moveCursor(0, 0, center, 0);
    cout << "|_____|__|__|_____| |_|  \n";
    delayMs(100);
}

void GUI::displayMenu() {
    displayTitleHeader();

    // HEADER'S BOTTOM BORDER
    space(3);
    displayBlockFormat(132, 2, '#');
    space(3);

    // MENU TEXT
    displayContinueText();
    space(5);
    displayStartText();
    space(6);
    displayExitText();

    // MENU'S BOTTOM MARGIN
    space(5);
    displayFooter(2, '#');
}

void GUI::displayContinueMenu() {
    displayTitleHeader();

    // HEADER'S BOTTOM BORDER
    space(3);
    displayBlockFormat(132, 2, '#');
    space(3);
}

void GUI::displayStartMenu() {
    displayTitleHeader();

    // HEADER'S BOTTOM BORDER
    space(3);
    displayBlockFormat(132, 2, '#');
    space(3);
}