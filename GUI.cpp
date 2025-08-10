/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "GUI.h"
#include "Scenes.h"
#include "Utility.h"
#include "Station.h"
using namespace std;
/*--------------------- GUI DEFINITIONS ----------------------*/
int saveFileNum = 0;
SaveData currentSaveFile; // holds current saved data

// Displays all current values of the loaded save file for debbuging 
void debugCurrentSaveFile() {
    cout << "=== DEBUG: Current Save File ===\n";
    cout << "Character Name: " << currentSaveFile.player_data.characterName << "\n";
    cout << "Stand Name: " << currentSaveFile.player_data.standName << "\n";
    cout << "Level: " << currentSaveFile.player_data.level << "\n";
    cout << "Day: " << currentSaveFile.player_data.day << "\n";
    cout << "Chapter: " << currentSaveFile.player_data.currentChapter << "\n";
    cout << "Save Time: " << currentSaveFile.player_data.saveTimestamp << "\n";
    cout << "Playtime: " << currentSaveFile.player_data.playtimeDuration << " minutes\n\n";
  
    cout << "Money: $" << currentSaveFile.financial_statistics.money << "\n";
    cout << "Revenue: $" << currentSaveFile.financial_statistics.revenue << "\n";
    cout << "Expenses: $" << currentSaveFile.financial_statistics.expenses << "\n\n";
  
    cout << "Stock:\n";
    cout << "  Lemons: " << currentSaveFile.stocks.lemons << "\n";
    cout << "  Water: " << currentSaveFile.stocks.water << " ml\n";
    cout << "  Sugar: " << currentSaveFile.stocks.sugar << " g\n";
    cout << "  Ice: " << currentSaveFile.stocks.ice << "\n";
    cout << "  Cups: " << currentSaveFile.stocks.cups << "\n";
    cin.get();
}

// Game's header
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

// Creation of a new game file with character and stand name
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

// Loads save data or starts new game based on the save file or when the last part the player exited
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
    string characterName = data[saveFileNum]["player_data"]["characterName"];
    string standName = data[saveFileNum]["player_data"]["standName"];

    if (day == 1 && characterName == "" && standName == "")
        createNewGame();
    else {
        currentSaveFile = loadSaveData(saveFileNum, "saveFiles.json");
        startGame();
    }
}

// Shows all existing save files 
void displaySaveFiles() { // Invalid json read
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
  
  	 // Show eaxh save' summary 
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

// Displays stock and status information 
void displayInformation() {
    // Get data from json file
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
        cerr << "Could not open saveFiles.json\n";
        return;
    }

    json data;
    file >> data;

    int lemon = currentSaveFile.stocks.lemons;
    int water = currentSaveFile.stocks.water;
    int sugar = currentSaveFile.stocks.sugar;
    int ice = currentSaveFile.stocks.cups;
    int cups = currentSaveFile.stocks.ice;

    // Display Day & Chapter
    goTo(3, 2);
    cout << " Day " << currentSaveFile.player_data.day << " || Chapter " << currentSaveFile.player_data.currentChapter << " #";

    // Display Stocks
    goTo(0, 21);
    moveCursor(0, 0, 58, 0); cout << "STOCKS" << '\n';
    space(1);
    moveCursor(0, 0, 56, 0); cout << setw(7) << "Lemon: " << lemon << '\n';
    moveCursor(0, 0, 56, 0); cout << setw(7) << "Water: " << water << "mL" << '\n';
    moveCursor(0, 0, 56, 0); cout << setw(7) << "Sugar: " << sugar << "g" << '\n';
    moveCursor(0, 0, 56, 0); cout << setw(7) << "Ice: " << ice << '\n';
    moveCursor(0, 0, 56, 0); cout << setw(7) << "Cups: " << cups << '\n';
}

// Converts 24-hour format to 12-hour with AM/PM 
string formatTime(int hour) {
    int displayHour = hour % 12;
    if (displayHour == 0) displayHour = 12;
    string period = (hour < 12) ? "A.M." : "P.M.";
    return (hour < 10 ? "0" : "") + to_string(displayHour) + ":00 " + period;
}

// Upates money displays 
void updateMoney() {
    goTo(40, 2);
    cout << "$ " << currentSaveFile.financial_statistics.money;
}

// Displays current time in game time
void displayTime(int currentHour) {
    goTo(62, 2);
    cout << formatTime(currentHour) << endl;
}

// Increments and updates time
void updateTime(int &currentHour) {
    if (currentHour < 20) { // up to 8:00 P.M.
        currentHour++;
    }
    goTo(62, 2);
    cout << formatTime(currentHour) << endl;
}

time_t parseTimestamp(const string& timestamp) {
    tm t = {};
    istringstream ss(timestamp);
    ss >> get_time(&t, "%Y-%m-%d %H:%M");
    return mktime(&t);  // Convert to time_t for comparison
}
    
// Loads the most recent save file 
void continueGame() {
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
    cerr << "Could not open saveFiles.json\n";
    cin.get();
    return;
    }

    json data;
    file >> data;

    int latestIndex = -1;
    time_t latestTime = 0;

    for (int i = 0; i < data.size(); ++i) {
        string timestampStr = data[i]["player_data"]["saveTimestamp"];
        time_t currentTime = parseTimestamp(timestampStr);

        if (latestIndex == -1 || currentTime > latestTime) {
            latestIndex = i;
            latestTime = currentTime;
        }
    }
    saveFileNum = latestIndex;
    currentSaveFile = loadSaveData(saveFileNum, "saveFiles.json");
    startGame();
  }

// Displays the save file selection menu
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

// Main menu for the game 
void displayMainMenu() {
    playBackgroundMusic("backgroundMusic.mp3", 70);
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
        playSFX("navigateOption.wav", 30);
        if (key == 72) { // If 'Up Arrow' key is pressed
            current = (current - 1 + optionCount) % optionCount;
        } else if (key == 80) { // If 'Down Arrow' key is pressed
            current = (current + 1) % optionCount;
        } else if (key == 13) { // If 'Enter' key is pressed
            playSFX("selectOption.wav", 30);
            clearScreen();
            break;
        }
    }

    // Navigate to the next screen
    if (current == 0) continueGame();
    else if (current == 1) displayStartMenu();
    else displayExitMenu();
}