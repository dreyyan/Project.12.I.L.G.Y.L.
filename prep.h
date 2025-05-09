#ifndef DAY_PREPARATION_H
#define DAY_PREPARATION_H
#include "Portfolio.h"
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
void pressEnterToContinue();
// Main day preparation menu
void displayDayPrepMenu();

// UTILITY
void updateMessage();
void errorMessage();
void clearState();

// Inventory management
void displaySupplyMenu();
void displaySupplyCosts();
bool checkStockLevels();

// Weather forecast
void displayWeatherForecast(Weather& forecast);
Weather generateWeatherForecast();
void updateWeatherEffects(Weather& forecast);

// Price setting
void setPrice();
double calculateSuggestedPrice(const Recipe& recipe, const Weather& forecast);

// Planning overview
void displayDayPlan();
void saveDayPlan();
DayPlan generateDefaultPlan();
DayPlan generateDefaultPlan(const Weather& forecast);

// Start the day!
void finalizeDayPrep();

#endif // DAY_PREPARATION_H