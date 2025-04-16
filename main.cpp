/*----------------------- HEADER FILES -----------------------*/
#include <iostream>
#include "Utility.h"
#include "GUI.h"
#include "Scenes.h"
using namespace std;

// 1. Compilation
// g++ -o test main.cpp Utility.cpp GUI.cpp Scenes.cpp

// 2. Run executable(.exe) in external console
// Note: Edit path to your project
// CMD:
// Start-Process "cmd.exe" -ArgumentList "/k", "C:\Code\.projects\Project.12.I.L.G.Y.L\test.exe"
// PowerShell:
// Start-Process "powershell.exe" -ArgumentList "-NoExit", "-Command", "C:\Code\.projects\Project.12.I.L.G.Y.L\test.exe

int main() {
    hideCursor();
    // displayMainMenu();
    // displayStartMenu();
    // createNewGame();
    // playCutscene1();
    goToGameArea();

    cin.get();
    return 0;
}