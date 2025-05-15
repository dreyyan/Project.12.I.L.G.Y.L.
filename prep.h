#ifndef DAY_PREPARATION_H
#define DAY_PREPARATION_H
#include "Portfolio.h"
/*------------------- STRUCT DEFINITIONS -------------------*/
// Defines the recipe configuration for lemonade
/* This structures contains all parameters needed to prepare lemonade, 
   ingredients and pricing information. */
struct Recipe {
    int lemons;         // Number of lemons per pitcher
    int sugar;          // Grams of sugar per pitcher
    int ice;            // Ice cubes per cup
    double price;       // Price per cup
    int waterRatio;     // Amount of water in mL per pitcher
};

// Weather conditions that affect lemonade sales
// Contains current weather arameters and the calculated effect o potential sales volume.
struct Weather {
    string condition;  // Sunny, Partly Cloudy, Fair, Cloudy, Stormy
    int temperature;        // Temperature in Celsius
    double salesMultiplier; // How weather affects sales
};

// Comprehensive day planning information
/* Combines recipe, weather forecast, and business metrics for planning 
   a complete day of lemonade sales. */
struct DayPlan {
    Recipe recipe;
    Weather forecast;
    double marketingBudget;  // Daily budget for marketing activities
    int expectedCustomers;   // Projected number of customers based on weather and marketing
    double profitEstimate;   // Calculated estimated profit for the day
};
/*------------------- FUNCTION PROTOTYPES -------------------*/
// Utility function to pause program execution until user presses Enter
void pressEnterToContinue();
// Displays the main day preparation menu options
void displayDayPrepMenu();

/*------------------- UTILITY FUNCTIONS -------------------*/
// Updates status message to the user
void updateMessage();
// Displays an error message to the user
void errorMessage();
// Resets all state variables to default values
void clearState();

/*------------------- INVENTORY MANAGEMENT -------------------*/
// Shows the supply management interface
// Allows user to view current inventory and purchase additional supplies
void displaySupplyMenu();
// Displays the current costs of ingredients and supplies
void displaySupplyCosts();
// Verifies if current inventory levels are sufficient for planned sales
bool checkStockLevels();

/*------------------- WEATHER FORECAST -------------------*/
// Shows the weather forecast for the day
void displayWeatherForecast(Weather& forecast);
// Generates a random weather forecast for the day
Weather generateWeatherForecast();
// Updatesthe sales based on the weather forecast
void updateWeatherEffects(Weather& forecast);

/*------------------- PRICE MANAGEMENT -------------------*/
// Interface for setting the lemonade price
void setPrice();
// Algorithm to calculate optimal price based on recipe costs and weather
double calculateSuggestedPrice(const Recipe& recipe, const Weather& forecast);

/*------------------- DAY PLANNING -------------------*/
// Displays comprehensive plan for the day
void displayDayPlan();
// Saves the current day plan to a file
void saveDayPlan();
// Creates a default day plan with balanced parameters
DayPlan generateDefaultPlan();
// Creates a default day plan that factors in weather
DayPlan generateDefaultPlan(const Weather& forecast);

/*------------------- DAY EXECUTION -------------------*/
// Completes day preperation and transitions to the sales simulation
void finalizeDayPrep();

#endif // DAY_PREPARATION_H