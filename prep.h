#ifndef DAY_PREPARATION_H
#define DAY_PREPARATION_H
/*----------------------- HEADER FILES -----------------------*/
#include <string>

#include "Portfolio.h"
#include "GUI.h"
#include "Scenes.h"
using namespace std;
/*------------------- STRUCT DEFINITIONS -------------------*/
struct Recipe {
    int lemons;         // Number of lemons per pitcher
    int sugar;          // Grams of sugar per pitcher
    int ice;            // Ice cubes per cup
    double price;       // Price per cup
    int waterRatio;     // Amount of water in mL per pitcher
};

struct Weather {
    string condition;  // Sunny, Cloudy, Rainy, etc.
    int temperature;        // Temperature in Celsius
    double salesMultiplier; // How weather affects sales
};

struct DayPlan {
    Recipe recipe;
    Weather forecast;
    double marketingBudget;
    int expectedCustomers;
    double profitEstimate;
};
/*------------------- FUNCTION PROTOTYPES -------------------*/
// Main day preparation menu
void displayDayPrepMenu();

// UTILITY
void updateMessage();
void errorMessage();
void clearState();

// Recipe management
void displayRecipeMenu();
void adjustRecipe(Recipe& currentRecipe);
void displayRecipeStats(const Recipe& recipe);
void saveRecipe(Recipe& recipe, const char* recipeName); 
Recipe loadRecipe(const char* recipeName);

// Inventory management
void displaySupplyMenu();
void displaySupplyCosts();
bool checkStockLevels(const SaveData& saveData, const Recipe& recipe, int expectedCups);

// Weather forecast
void displayWeatherForecast(Weather& forecast);
Weather generateWeatherForecast();
void updateWeatherEffects(Weather& forecast);

// Price setting
void setPrice(Recipe& recipe);
double calculateSuggestedPrice(const Recipe& recipe, const Weather& forecast);

// Planning overview
void displayDayPlan(const DayPlan& plan);
void saveDayPlan(const DayPlan& plan);
DayPlan generateDefaultPlan();

// Start the day!
void finalizeDayPrep(SaveData& saveData, DayPlan& plan);

#endif // DAY_PREPARATION_H