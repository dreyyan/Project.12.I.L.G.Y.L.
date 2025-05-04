#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
using namespace std;

// PLAYER STATISTICS:
// Saves the player's data
struct PlayerData {
    string characterName;       // Name of the created character
    string standName;           // Name of the Lemonade stand
    int level;                  // Current level of the player
    int day;                    // Current day of the story
    int currentChapter;         // Current chapter of the story
    string saveTimestamp;
    int playtimeDuration;
};

// FINANCIAL STATISTICS:
// Tracks the financial performance of the player's business
struct FinancialStats {
    double money;               // Current cash available
    double revenue;             // Total income before expenses
    double expenses;            // Cost of operation
};

struct Stocks {
    int lemons;
    int water;                  // in mL
    int sugar;                  // in g
    int ice;
    int cups;
};

// MASTERSTRUCT: SaveData
// Object to store all information
struct SaveData {
    PlayerData player_data;
    FinancialStats financial_statistics;
    Stocks stocks;
};

#endif