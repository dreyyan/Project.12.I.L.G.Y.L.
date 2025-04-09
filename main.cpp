/*----------------------- HEADER FILES -----------------------*/
#include <iostream>
#include "Utility.h"
#include "GUI.h"
#include "Portfolio.h"
using namespace std;

// 1. Compilation
// g++ -o test main.cpp Utility.cpp GUI.cpp

// 2. Run executable(.exe) in external console
// Note: Edit path to your project
// CMD:
// Start-Process "cmd.exe" -ArgumentList "/k", "C:\Code\.projects\Project.12.I.L.G.Y.L\test.exe"
// PowerShell:
// Start-Process "powershell.exe" -ArgumentList "-NoExit", "-Command", "C:\Code\.projects\Project.12.I.L.G.Y.L\test.exe

// SaveData save;
// // PLAYER DATA
// save.player_data.characterName = "Lemo";
// save.player_data.standName = "Lemonay";
// save.player_data.level = 3;
// save.player_data.currentChapter = 2;

// // FINANCIAL STATISTICS
// save.financial_statistics.money = 250.0;
// save.financial_statistics.revenue = 800.0;
// save.financial_statistics.expenses = 550.0;
// save.financial_statistics.debt = 100.0;

// // PERSONAL STATISTICS
// save.personal_statistics.happiness = 75.0;
// save.personal_statistics.stress = 40.0;
// save.personal_statistics.motivation = 85.0;

// // BUSINESS STATISTICS
// save.business_statistics.employees = 2;
// save.business_statistics.popularity = 65;
// save.business_statistics.recipesOwned = 3;

// // GAME STATISTICS
// save.game_statistics.productsSold = 340;
// save.game_statistics.totalProfit = 250.0; // revenue - expenses
// save.game_statistics.highestDailyProfit = 120.0;

int main() {
    hideCursor();
    displayMainMenu();
    displayStartMenu();
    delayS(3);
    exit(0);
    return 0;
}