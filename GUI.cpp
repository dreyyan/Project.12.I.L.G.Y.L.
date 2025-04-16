/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "GUI.h"
#include "Scenes.h"
#include "Utility.h"
using namespace std;
/*--------------------- GUI DEFINITIONS ----------------------*/
int saveFileNum = 0;
SaveData currentSaveFile;

void displayHeader() {
    space(1);
    displaySpacedFormat(72, '#');
    space(1);

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

void createNewGame() {
    // Loops infinitely until user saves changes
    while (true) {
        clearScreen();
        displayHeader();
        space(2);
        
        cout << "    Enter Character Name: ";
        showCursor();
        getline(cin, currentSaveFile.player_data.characterName);
        space(2);
    
        displaySpacedFormat(72, '=');
        space(2);
        cout << "    Enter Name of Lemonade Stand: ";
        getline(cin, currentSaveFile.player_data.standName);
        space(2);
        hideCursor();
    
        displaySpacedFormat(72, '=');
        space(1);
    
        centerText("Save Changes?:");
        centerText("    NO       YES    ");

        /*--------------------- START of NAVIGATION ----------------------*/
        const int optionCount = 2;
        int x[optionCount] = {32, 41};
        int y[optionCount] = {28, 28};
        int current = 0;
        char key;
    
        while (true) {
            // Draw all cursors
            for (int i = 0; i < optionCount; ++i) {
                // Draw ">>" at left
                goTo(x[i] - 3, y[i]);
                cout << (i == current ? ">" : " ");
        
                // Erase previous "<<" at right if not the current
                if (i != current) {
                    if (i == 0) moveCursor(0, 0, 5, 0);
                    else if (i == 1) moveCursor(0, 0, 6, 0);
                    cout << " ";
                }
        
                // Draw "<<" at right for current option
                if (i == current) {
                    if (current == 0) moveCursor(0, 0, 5, 0);
                    else if (current == 1) moveCursor(0, 0, 6, 0);
                    cout << "<";
                }
            }
        
            key = _getch();
            if (key == 75) { // If 'Left Arrow' key is pressed
                current = (current - 1 + optionCount) % optionCount;
            } else if (key == 77) { // If 'Right Arrow' key is pressed
                current = (current + 1) % optionCount;
            } else if (key == 13) { // If 'Enter' key is pressed
                break;
            }
        }

        // Navigate to the next screen
        if (current == 0) continue;
        else {
            displayNewGameCutscene();
            startGame();
            break;
        }
        /*---------------------- END of NAVIGATION -----------------------*/
    }
}

void createOrLoad() {
    // Get data from json file
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
      cerr << "Could not open saveFiles.json\n";
      return;
    }
  
    json data;
    file >> data;
    int day = data[saveFileNum]["player_data"]["day"];

    // If day is 1, create new game, else, load game area
    if (day == 1) createNewGame();
    else {
        currentSaveFile = loadSaveData(saveFileNum, "saveFiles.json");
        startGame();
    }
}

void displaySaveFiles() {
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
      cerr << "Could not open saveFiles.json\n";
      return;
    }
  
    json data;
    file >> data;
  
    for (int i = 0; i < data.size(); ++i) {
      space(1);
      if (i != 0) displaySpacedFormat(72, '=');
      centerText("SAVE #" + to_string(i + 1));
      space(1);
  
      string name = data[i]["player_data"]["characterName"];
      string stand = data[i]["player_data"]["standName"];
      int lvl = data[i]["player_data"]["level"];
      int day = data[i]["player_data"]["day"];
      int chapter = data[i]["player_data"]["currentChapter"];
      float money = data[i]["financial_statistics"]["money"];
  
      cout << "  " << setw(10) << "Name: " << name << '\n'; delayMs(50);
      cout << "  " << setw(10) << "Stand: " << stand << '\n'; delayMs(50);
      cout << "  " << setw(10) << "Lvl.: " << lvl << '\n'; delayMs(50);
      cout << "  " << setw(10) << "Day: " << day << '\n'; delayMs(50);
      cout << "  " << setw(10) << "Chapter: " << chapter << '\n'; delayMs(50);
      cout << "  " << setw(10) << "Money: " << money << " php\n"; delayMs(50);
    }

    /*--------------------- START of NAVIGATION ----------------------*/
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
            break;
        }
    }

    // Set savefile # to the current
    saveFileNum = current;
    createOrLoad();
    /*---------------------- END of NAVIGATION -----------------------*/
}

void displayInformation() {
    // Get data from json file
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
        cerr << "Could not open saveFiles.json\n";
        return;
    }

    json data;
    file >> data;

    int lemon = data[saveFileNum]["stocks"]["lemon"];
    int water = data[saveFileNum]["stocks"]["water"];
    int sugar = data[saveFileNum]["stocks"]["sugar"];
    int ice = data[saveFileNum]["stocks"]["ice"];
    int cups = data[saveFileNum]["stocks"]["cups"];

    // Display Day
    goTo(34, 2);
    cout << "DAY " << data[saveFileNum]["player_data"]["day"];

    // Display Stocks
    goTo(0, 20);
    moveCursor(0, 0, 62, 0); cout << "STOCKS" << '\n';
    space(1);
    moveCursor(0, 0, 60, 0); cout << setw(7) << "Lemon: " << lemon << '\n';
    moveCursor(0, 0, 60, 0); cout << setw(7) << "Water: " << water << '\n';
    moveCursor(0, 0, 60, 0); cout << setw(7) << "Sugar: " << sugar << '\n';
    moveCursor(0, 0, 60, 0); cout << setw(7) << "Ice: " << ice << '\n';
    moveCursor(0, 0, 60, 0); cout << setw(7) << "Cups: " << cups << '\n';
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
    
        // 
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