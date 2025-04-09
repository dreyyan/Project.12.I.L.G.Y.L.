/*----------------------- HEADER FILES -----------------------*/
#include <algorithm>
#include <conio.h>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <vector>
#include "Utility.h"
using namespace std;
/*------------------- UTILITY DEFINITIONS --------------------*/
void displayFormat(size_t length, char symbol) {
    string repeated(length, symbol);
    cout << repeated;
    delayMs(50);
}

void displaySpacedFormat(size_t length, char symbol) {
    string repeated(length, symbol); // create the string with repeated characters
    cout << repeated;
    delayMs(50);
    cout << '\n';
}

void displayAlternatingFormat(size_t length, char firstSymbol, char secondSymbol) {
    for (size_t i = 0; i < length; ++i) {
        cout << (i % 2 == 0 ? firstSymbol : secondSymbol);
    } delayMs(50);
}

void displayBlockFormat(size_t width, size_t height, char symbol) {
    for (size_t i = 0; i < height; ++i) {
        displayFormat(width, symbol);
    }
}

void displayBlockSpacedFormat(size_t width, size_t height, char symbol) {
    for (size_t i = 0; i < height; ++i) {
        string repeated(width, symbol); // create the string with repeated characters
        cout << repeated;
        delayMs(50);
        cout << '\n';
    }
}

void space(size_t n) {
    for (size_t i = 0; i < n; ++i) { cout << '\n'; }
}

void delayS(int s) {
    this_thread::sleep_for(chrono::seconds(s));
}

void delayMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void characterDelayAnimation(string stringInput, int ms) {
    for (int i = 0; i < stringInput.length(); ++i) {
        cout << stringInput[i];
        this_thread::sleep_for(chrono::milliseconds(ms));
    }
}

void lineDelayAnimation(string stringInput, int ms) {
    cout << stringInput;
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void pressEnter(string process) {
    characterDelayAnimation("Press 'Enter' to " + process + "...", 25);
    cin.get();
}

void trim(string& stringInput) {
    stringInput.erase(0, stringInput.find_first_not_of(" ")); // Remove leading whitespaces
    stringInput.erase(stringInput.find_last_not_of(" ") + 1); // Remove trailing whitespaces
}

void toLowercase(string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::tolower);
}

void toUppercase(string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::toupper);
}

void capitalize(string& stringInput) {
    stringInput[0] = toupper(stringInput[0]);
    for (int i = 1; i < stringInput.length(); ++i) {
        stringInput[i] = tolower(stringInput[i]);
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void spinningAnimation(const string& toGenerate, int x) {
    char spinner_characters[4] = {'|', '/', '-', '\\'};
    cout << "...generating " << toGenerate << " [ ]";
    goTo(1, x);
    for (int i = 0; i < 40; ++i) {
        cout << spinner_characters[i % 4];
        delayMs(50);
        goTo(1, x);
    } goTo(1, x + 2); space(1);
}

void loadingBarAnimation(int x) {
    int percentage = 0;
    cout << " [          ] " << percentage << '\n';
    for (int i = 0; i < 10; ++i) {
        goTo(1, x);
        cout << '#';
    }
}

void centerText(string textInput) {
    int consoleWidth = 72;
    int margin = (consoleWidth - textInput.length()) / 2;

    // Display Header
    displayFormat(margin, ' ');
    cout << textInput;
    displayFormat(margin, ' ');
}

void hideCursor() {
    cout << "\e[?25l";
}
  
void showCursor() {
    cout << "\e[?25h";
}

void moveCursor(int up, int down, int right, int left) {
    cout << "\033[" << (up >= 0 ? up : 0) << 'A';
    cout << "\033[" << (down >= 0 ? down : 0) << 'B';
    cout << "\033[" << (right >= 0 ? right : 0) << 'C';
    cout << "\033[" << (left >= 0 ? left : 0) << 'D';
}

void goTo(int y, int x) {
    cout << "\033[" << x << ';' << y << 'H';
}