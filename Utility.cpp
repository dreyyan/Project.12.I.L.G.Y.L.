/*----------------------- HEADER FILES -----------------------*/
#include <algorithm>
#include <chrono>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "Utility.h"
using namespace std;

sf::Music music;
sf::Music SFX;
/*------------------- UTILITY DEFINITIONS --------------------*/
// Displays a repeated symbol line with a short delay
void displayFormat(size_t length, char symbol) {
    string repeated(length, symbol);
    cout << repeated;
    delayMs(50);
}


// Adds a newline at the end
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
        cout << '\n';
    }
}

void displayBlockSpacedFormat(size_t width, size_t height, char symbol) {
    for (size_t i = 0; i < height; ++i) {
        string repeated(width, symbol); // create the string with repeated characters
        cout << repeated;
        delayMs(50);
        cout << '\n';
    } cout << '\n';
}

void displayBorder(size_t height, char symbol) {
    for (int i = 0; i < height; ++i) {
            cout << '#';
            string repeated(70, ' ');
            cout << repeated;
            cout << '#';
        cout << '\n';
    }
}

// Displays horizontal lines at specified coordinates 
void displayHLine(int x, int y, size_t length, char symbol) {
    goTo(x, y);
    for (int i = 0 ; i < length; ++i) {
        cout << symbol;
    }
}

// Draws a vertical line at specified coordinates 
void displayVLine(int x, int y, size_t length, char symbol) {
    goTo(x, y);
    for (int i = 0 ; i < length; ++i) {
        cout << symbol;
        goTo(x, y + i);
    }
}

void space(size_t n) {
    for (size_t i = 0; i < n; ++i) { cout << '\n'; }
}

// Delays execution for given seconds 
void delayS(int s) {
    this_thread::sleep_for(chrono::seconds(s));
}

// DelaYs execution for given milliseconds 
void delayMs(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Prints character one by one 
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

// Prompts user to press enter to proceed 
void pressEnter(string process) {
    characterDelayAnimation("Press 'Enter' to " + process + "...", 25);
    cin.get();
    playSFX("selectOption.wav", 30);
}

void trim(string& stringInput) {
    stringInput.erase(0, stringInput.find_first_not_of(" ")); // Remove leading whitespaces
    stringInput.erase(stringInput.find_last_not_of(" ") + 1); // Remove trailing whitespaces
}

// Converts string to lowercase 
void toLowercase(string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::tolower);
}

// Converts string to lowercase 
void toUppercase(string& stringInput) {
    transform(stringInput.begin(), stringInput.end(), stringInput.begin(), ::toupper);
}

// Capitalizes first letter, makes the rest lowercase
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

// Loading visual 
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

// Incompplete loading animation 
void loadingBarAnimation(int x) {
    int percentage = 0;
    cout << " [          ] " << percentage << '\n';
    for (int i = 0; i < 10; ++i) {
        goTo(1, x);
        cout << '#';
    }
}

// Center text in a 72-character wide console 
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

// Moves cursor up/down/right/left by specified values 
void moveCursor(int up, int down, int right, int left) {
    cout << "\033[" << (up >= 0 ? up : 0) << 'A';
    cout << "\033[" << (down >= 0 ? down : 0) << 'B';
    cout << "\033[" << (right >= 0 ? right : 0) << 'C';
    cout << "\033[" << (left >= 0 ? left : 0) << 'D';
}

// Moves cursor to specific row and column 
void goTo(int y, int x) {
    cout << "\033[" << x << ';' << y << 'H';
}

// Loads saveData from a json file
SaveData loadSaveData(int saveFileNum, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open " + filename);
    }
  
    json data;
    try {
      file >> data;
    } catch (json::parse_error& e) {
      throw std::runtime_error("JSON parsing error: " + std::string(e.what()));
    }
  
    if (!data.is_array() || saveFileNum < 0 || saveFileNum >= data.size()) {
      throw std::runtime_error("Invalid save file number: " + std::to_string(saveFileNum));
    }
  
    auto j = data[saveFileNum];
    SaveData savefile;
  
    try {
     // Player data
      savefile.player_data.characterName     = j.at("player_data").at("characterName");
      savefile.player_data.standName         = j.at("player_data").at("standName");
      savefile.player_data.level             = j.at("player_data").at("level");
      savefile.player_data.day               = j.at("player_data").at("day");
      savefile.player_data.currentChapter    = j.at("player_data").at("currentChapter");
  
  	 // Loads financial statistics 
      savefile.financial_statistics.money    = j.at("financial_statistics").at("money");
      savefile.financial_statistics.revenue  = j.at("financial_statistics").at("revenue");
      savefile.financial_statistics.expenses = j.at("financial_statistics").at("expenses");
  
  	 // Loads stock items
      savefile.stocks.lemons = j.at("stocks").at("lemons");
      savefile.stocks.water  = j.at("stocks").at("water");
      savefile.stocks.sugar  = j.at("stocks").at("sugar");
      savefile.stocks.ice    = j.at("stocks").at("ice");
      savefile.stocks.cups   = j.at("stocks").at("cups");

     // Load business plan
      savefile.plan.price   = j.at("plan").at("price");
      savefile.plan.expectedCustomers   = j.at("plan").at("expectedCustomers");
      savefile.plan.profitEstimate   = j.at("plan").at("profitEstimate");
      savefile.plan.condition   = j.at("plan").at("condition");
      savefile.plan.temperature   = j.at("plan").at("temperature");
    } catch (json::out_of_range& e) {
      throw std::runtime_error("Missing or invalid fields in save data: " + std::string(e.what()));
    }
  
    return savefile;
  }
  
  void playBackgroundMusic(std::string musicFileName, int volume) {
    // Load music from a file (must remain on disk while playing)
    if (!music.openFromFile("assets/" + musicFileName)) {
        std::cerr << "Error loading music file!" << std::endl;
        return;
    }

    music.setVolume(volume); // Set volume
    music.setLoop(true); // Optional: loop the music
    music.play();
}

void playSFX(std::string musicFileName, int volume) {
    // Load music from a file (must remain on disk while playing)
    if (!SFX.openFromFile("assets/" + musicFileName)) {
        std::cerr << "Error loading music file!" << std::endl;
        return;
    }

    SFX.setVolume(volume); // Set volume
    SFX.play();
}