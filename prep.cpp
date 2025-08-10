/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>

#include "Utility.h"
#include "prep.h"
#include "GUI.h"
#include "Scenes.h"
#include "Portfolio.h"
using namespace std;

// Constants for supply costs - used for pricing calculations and purchasing
const double LEMON_COST = 5;  // per pack(12 pcs.)
const double SUGAR_COST = 1.25;  // per sugar bag(1kg)
const double WATER_COST = 1; // per gallon(3785ml)
const double ICE_COST = 2; // per pack(100 cubes)
const double CUP_COST = 4;   // per pack(100 cups)

// Displays the day preparation menu and handles navigation
// This is the main entry point for the day preparation phase
void displayDayPrepMenu() {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= DAY -=- PREPARATION =- ]");
    goTo(3, 3); cout << fixed << setprecision(2) << "$ " << currentSaveFile.financial_statistics.money;
    goTo(64, 3); cout << "DAY " << currentSaveFile.player_data.day;
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    displayVLine(26, 5, 22, '#');
    goTo(0, 7);
    moveCursor(0, 0, 4, 0); cout << "[ SUPPLIES ";
    space(2);
    displaySpacedFormat(25, '=');
    space(1);
    moveCursor(0, 0, 4, 0); cout << "[ WEATHER FORECAST";
    space(2);
    displaySpacedFormat(25, '=');
    space(1);
    moveCursor(0, 0, 4, 0); cout << "[ PRICING";
    space(2);
    displaySpacedFormat(25, '=');
    space(1);
    moveCursor(0, 0, 4, 0); cout << "[ DAY PLAN";
    space(2);
    displaySpacedFormat(25, '=');
    space(1);
    moveCursor(0, 0, 4, 0); cout << "[ START DAY";
    space(2);
    displaySpacedFormat(72, '#');
    goTo(1, 1);

    // Generate a new weather forecast for the day
    static Weather dailyForecast = generateWeatherForecast();

    // Store forecast information in the current save file for later use
    currentSaveFile.plan.condition = dailyForecast.condition;
    currentSaveFile.plan.temperature = dailyForecast.temperature;
    
    /*--------------------- START OF NAVIGATION ----------------------*/
    const int optionCount = 5;
    int x[optionCount] = {2, 2, 2, 2, 2};
    int y[optionCount] = {7, 11, 15, 19, 23};
    int current = 0;
    char key;
    
    // Menu navigation loop
    while (true) {
        // Draw '>' cursor for the currently selected option
        for (int i = 0; i < optionCount; ++i) {
            // Draw ">" at left
            goTo(x[i], y[i]);
            cout << (i == current ? ">" : " ");
        }
        
        key = _getch();
        playSFX("navigateOption.wav", 30);
        if (key == 72) { // If 'Up Arrow' key is pressed
            current = (current - 1 + optionCount) % optionCount;
        } else if (key == 80) { // If 'Down Arrow' key is pressed
            current = (current + 1) % optionCount;
        } else if (key == 13) { // If 'Enter' key is pressed
            playSFX("selectOption.wav", 30);
            break;
        }
    }
    
    // Navigate to the selected option
    switch (current) {
        case 0: {
            displaySupplyMenu();
            break;
        }
        case 1: {
            displayWeatherForecast(dailyForecast);
            break;
        }
        case 2: {
            setPrice();
            break;
        }
        case 3: {
            displayDayPlan();
            break;
        }
        case 4: {
            finalizeDayPrep();
            break;
        }
    }
    /*---------------------- END OF NAVIGATION -----------------------*/
}

/*------------------- UTILITY FUNCTIONS -------------------*/
// Displays a success message when a setting is updated
void updateMessage(string message) {
    space(2);
    centerText(" + " + message + " updated successfully!");
    space(1);
}

// Displays an error message and clears the input buffer
void errorMessage(string message) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    centerText("ERROR: " + message);
}

// Handles input errors by clearing the state and showing an error message
void clearState() {
    space(1);
    errorMessage("Please enter a valid number");
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    goTo(1, 24); cout << "          ";
    goTo(1, 23);
}

// Displays the supply purchase menu and handles transactions
// Allows the player to buy new supplies for their lemonade stand
void displaySupplyMenu() {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= PURCHASE -=- SUPPLIES =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    // Display current stock
    cout << "              $" << fixed << setprecision(2) << currentSaveFile.financial_statistics.money << endl;
    space(1);
    displaySpacedFormat(72, '=');
    centerText("# CURRENT STOCKS #");
    space(1);
    space(1);
    cout << setw(18) << "Lemons: " << currentSaveFile.stocks.lemons << " pcs. " << endl;
    cout << setw(18) << "Sugar: " << currentSaveFile.stocks.sugar << " g" << endl;
    cout << setw(18) << "Water: " << currentSaveFile.stocks.water << " mL" << endl;
    cout << setw(18) << "Ice: " << currentSaveFile.stocks.ice << " cube/s" << endl;
    cout << setw(18) << "Cups: " << currentSaveFile.stocks.cups << " pcs." << endl;
    space(1);
    
    displaySpacedFormat(72, '=');

    // Display prices
    centerText("# BUY SUPPLIES #");
    space(1);
    space(1);
    cout << setw(18) << "Lemons: $" << LEMON_COST << " /   12 pcs." << endl;
    cout << setw(18) << "Sugar: $" << SUGAR_COST << " / 1000 g" << endl;
    cout << setw(18) << "Water: $" << WATER_COST << " / 3785 mL" << endl;
    cout << setw(18) << "Ice: $" << ICE_COST << " /  100 cubes" << endl;
    cout << setw(18) << "Cups: $" << CUP_COST << " /  100 pcs." << endl;
    space(1);
    
    displaySpacedFormat(72, '#');
    space(1);

    // Initialize quantities and costs
    int lemonsToAdd = 0, sugarToAdd = 0, waterToAdd = 0, iceToAdd = 0, cupsToAdd = 0;
    // Set increment amounts for each purchase (matches package sizes)
    int lemonsIncrement = 12, sugarIncrement = 1000, waterIncrement = 3785, iceIncrement = 100, cupsIncrement = 100;
    // Set quantity multipliers (for future use if bulk purchasing is implemented)
    int lemonsQuantity = 1, sugarQuantity = 1, waterQuantity = 1, iceQuantity = 1, cupsQuantity = 1;
    double totalCost = 0.0;

    displayVLine(36, 5, 5, '#');
    goTo(46, 7);
    cout << "Total Cost: $" << totalCost;
    goTo(1, 29);
    centerText("Purchase Supplies(P)      Back (B)");

    // Display to-add values
    goTo(50, 21);
    cout << lemonsToAdd;
    goTo(50, 22);
    cout << sugarToAdd;
    goTo(50, 23);
    cout << waterToAdd;
    goTo(50, 24);
    cout << iceToAdd;
    goTo(50, 25);
    cout << cupsToAdd;

    // Display total units to be added
    goTo(66, 21);
    cout << '0';
    goTo(66, 22);
    cout << '0';
    goTo(66, 23);
    cout << '0';
    goTo(66, 24);
    cout << '0';
    goTo(66, 25);
    cout << '0';

    char choice;

    // Cursor navigation logic for supply selection
    const int optionCount = 5;
    int x[optionCount] = { 53, 53, 53, 53, 53 };
    int y[optionCount] = { 21, 22, 23, 24, 25 };
    int current = 0;
    int currentOption = 0;
    char key;
  
    // Supply purchase menu interaction loop
    while (true) {
        // Draw all cursors
        for (int i = 0; i < optionCount; ++i) {
            goTo(x[i], y[i]);
            cout << (i == current ? "[" : " ");
    
            if (i != current) {
                if (i == 0) moveCursor(0, 0, 11, 0);
                else if (i == 1) moveCursor(0, 0, 11, 0);
                else if (i == 2) moveCursor(0, 0, 11, 0);
                else if (i == 3) moveCursor(0, 0, 11, 0);
                else if (i == 4) moveCursor(0, 0, 11, 0);
                cout << " ";
            }
    
            if (i == current) {
                if (current == 0) moveCursor(0, 0, 11, 0);
                else if (current == 1) moveCursor(0, 0, 11, 0);
                else if (current == 2) moveCursor(0, 0, 11, 0);
                else if (i == 3) moveCursor(0, 0, 11, 0);
                else if (i == 4) moveCursor(0, 0, 11, 0);
                cout << "]";
            }
        }

        key = _getch();

        if (key == 72) { // 'Up Arrow' key
            playSFX("navigateOption.wav", 30);
            current = (current - 1 + optionCount) % optionCount;
            currentOption = current;
        } else if (key == 80) { // 'Down Arrow' key 
            playSFX("navigateOption.wav", 30);
            current = (current + 1) % optionCount;
            currentOption = current;
        } else if (key == 75) { // 'Left Arrow' key - decrease quantity
            switch (currentOption) {
                case 0: {
                    if (lemonsToAdd > 0) {
                        totalCost -= lemonsQuantity * LEMON_COST;
                        lemonsToAdd -= lemonsQuantity;
                        goTo(50, 21); cout << lemonsToAdd << ' ';
                        goTo(54 + lemonsToAdd, 21); cout << ' '; moveCursor(0, 0, 0, 1);
                        goTo(66, 21); cout << "      "; goTo(66, 21); cout << lemonsIncrement * lemonsToAdd;
                    } break;
                } case 1: {
                    if (sugarToAdd > 0) {
                        totalCost -= sugarQuantity * SUGAR_COST;
                        sugarToAdd -= sugarQuantity;
                        goTo(50, 22); cout << sugarToAdd << ' ';
                        goTo(54 + sugarToAdd, 22); cout << ' '; moveCursor(0, 0, 0, 1);
                        goTo(66, 22); cout << "      "; goTo(66, 22); cout << sugarIncrement * sugarToAdd;
                    } break;
                } case 2: {
                    if (waterToAdd > 0) {
                        totalCost -= waterQuantity * WATER_COST;
                        waterToAdd -= waterQuantity;
                        goTo(50, 23); cout << waterToAdd << ' ';
                        goTo(54 + waterToAdd, 23); cout << ' '; moveCursor(0, 0, 0, 1);
                        goTo(66, 23); cout << "      "; goTo(66, 23); cout << waterIncrement * waterToAdd;
                    } break;
                } case 3: {
                    if (iceToAdd > 0) {
                        totalCost -= iceQuantity * ICE_COST;
                        iceToAdd -= iceQuantity;
                        goTo(50, 24); cout << iceToAdd << ' ';
                        goTo(54 + iceToAdd, 24); cout << ' '; moveCursor(0, 0, 0, 1);
                        goTo(66, 24); cout << "      "; goTo(66, 24); cout << iceIncrement * iceToAdd;
                    } break;
                } case 4: {
                    if (cupsToAdd > 0) {
                        totalCost -= cupsQuantity * CUP_COST;
                        cupsToAdd -= cupsQuantity;
                        goTo(50, 25); cout << cupsToAdd << ' ';
                        goTo(54 + cupsToAdd, 25); cout << ' '; moveCursor(0, 0, 0, 1);
                        goTo(66, 25); cout << "      "; goTo(66, 25); cout << cupsIncrement * cupsToAdd;
                    } break;
                }
            }
        } else if (key == 77) { // 'Right Arrow' key - increase quantity
            switch (currentOption) {
                case 0: {
                    if (lemonsToAdd >= 0 && lemonsToAdd < 10) {
                        totalCost += lemonsQuantity * LEMON_COST;
                        lemonsToAdd += lemonsQuantity;
                        goTo(50, 21); cout << lemonsToAdd << ' ';
                        goTo(53 + lemonsToAdd, 21); cout << '*';
                        goTo(66, 21); cout << "      "; goTo(66, 21); cout << lemonsIncrement * lemonsToAdd;
                    } break;
                } case 1: {
                    if (sugarToAdd >= 0 && sugarToAdd < 10) {
                        totalCost += sugarQuantity * SUGAR_COST;
                        sugarToAdd += sugarQuantity;
                        goTo(50, 22); cout << sugarToAdd << ' ';
                        goTo(53 + sugarToAdd, 22); cout << '*';
                        goTo(66, 22); cout << "      "; goTo(66, 22); cout << sugarIncrement * sugarToAdd;
                    } break;
                } case 2: {
                    if (waterToAdd >= 0 && waterToAdd < 10) {
                        totalCost += waterQuantity * WATER_COST;
                        waterToAdd += waterQuantity;
                        goTo(50, 23); cout << waterToAdd << ' ';
                        goTo(53 + waterToAdd, 23); cout << '*';
                        goTo(66, 23); cout << "      "; goTo(66, 23); cout << waterIncrement * waterToAdd;
                    } break;
                } case 3: {
                    if (iceToAdd >= 0 && iceToAdd < 10) {
                        totalCost += iceQuantity * ICE_COST;
                        iceToAdd += iceQuantity;
                        goTo(50, 24); cout << iceToAdd << ' ';
                        goTo(53 + iceToAdd, 24); cout << '*';
                        goTo(66, 24); cout << "      "; goTo(66, 24); cout << iceIncrement * iceToAdd;
                    } break;
                } case 4: {
                    if (cupsToAdd >= 0 && cupsToAdd < 10) {
                        totalCost += cupsQuantity * CUP_COST;
                        cupsToAdd += cupsQuantity;
                        goTo(50, 25); cout << cupsToAdd << ' ';
                        goTo(53 + cupsToAdd, 25); cout << '*';
                        goTo(66, 25); cout << "      "; goTo(66, 25); cout << cupsIncrement * cupsToAdd;
                    } break;
                }
            }
        } else {
            // Handle other key inputs (like 'p' for purchase and 'b' for back)
            char key1 = tolower(key);
            if (key1 == 'p') { // 'p' key - execute purchase
                // Error handling: check if any items are selected
                if (totalCost == 0) {
                    playSFX("SFXError.mp3", 100);
                    goTo(0, 29);
                    cout << "                                  ";
                    goTo(0, 29);
                    centerText("You haven't selected any items!");
                    pressEnterToContinue();
                    displaySupplyMenu();
                    return;
                } 
                // Error handling: check if player has enough money
                else if (totalCost > currentSaveFile.financial_statistics.money) {
                    playSFX("SFXError.mp3", 100);
                    cout << "Total Cost: $" << totalCost << '\n';
                    cout << "Money: $" << currentSaveFile.financial_statistics.money << '\n';
                    cin.get();
                    goTo(0, 29);
                    cout << "                                  ";
                    goTo(0, 29);
                    centerText("You don't have enough money...");
                    pressEnterToContinue();
                    displaySupplyMenu();
                    return;
                } else {
                    playSFX("SFXPurchase.mp3", 70);
                    // Process the purchase: update stocks and financial records
                    currentSaveFile.stocks.lemons += (lemonsToAdd * lemonsIncrement);
                    currentSaveFile.stocks.sugar += (sugarToAdd * sugarIncrement);
                    currentSaveFile.stocks.water += (waterToAdd * waterIncrement);
                    currentSaveFile.stocks.ice += (iceToAdd * iceIncrement);
                    currentSaveFile.stocks.cups += (cupsToAdd * cupsIncrement);
                    currentSaveFile.financial_statistics.money -= totalCost;
                    currentSaveFile.financial_statistics.expenses += totalCost;
                    // Update expenses for financial tracking
                    currentSaveFile.financial_statistics.expenses += totalCost;
                    
                    goTo(1, 29);
                    centerText("Purchase complete!");
                    pressEnterToContinue();
                    displaySupplyMenu();
                }
            } else if (key1 == 'b') { // 'b' key - return to previous menu
                playSFX("selectOption.wav", 30);
                displayDayPrepMenu();
            }
        }

        // Update the displayed total cost
        goTo(59, 7);
        cout << "      ";
    
        goTo(59, 7);
        cout << totalCost;
    }
}

// Generates a random weather forecast for the day
// Weather affects customer demand and is a core gameplay mechanics
Weather generateWeatherForecast() {
    // Simple random weather generation
    Weather forecast;
    
    const std::string conditions[] = {"Sunny", "Partly Cloudy", "Fair", "Cloudy", "Stormy"};
    
    // Define temperature ranges for each condition
    const int tempMin[] = {28, 25, 22, 18, 15}; // Min temps for each condition
    const int tempMax[] = {40, 35, 32, 28, 25}; // Max temps for each condition
    
    // Setup random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> condDist(0, 4);
    
    // Select a random weather condition
    int condIdx = condDist(gen);
    forecast.condition = conditions[condIdx];
    
    /// Generate temperature based on the condition (within appropriate range)
    uniform_int_distribution<> tempDist(tempMin[condIdx], tempMax[condIdx]);
    forecast.temperature = tempDist(gen);
    
    // Set base sales multiplier based on conditions
    double multipliers[] = {1.5, 1.2, 1.0, 0.7, 0.4};
    forecast.salesMultiplier = multipliers[condIdx];
    
    // Fine-tune the sales multiplier based on temperature within the condition's range
    // For sunny days, hotter is better for lemonade sales
    if (forecast.condition == "Sunny" || forecast.condition == "Partly Cloudy") {
        // Calculate where in the temperature range this falls (0.0-1.0)
        double tempPercentile = (double)(forecast.temperature - tempMin[condIdx]) / 
                               (tempMax[condIdx] - tempMin[condIdx]);
        
        // Add up to 0.2 bonus for hotter temperatures
        forecast.salesMultiplier += tempPercentile * 0.2;
    }
    // For stormy/cloudy days, warmer weather helps mitigate the negative impact
    else if (forecast.condition == "Cloudy" || forecast.condition == "Stormy") {
        double tempPercentile = (double)(forecast.temperature - tempMin[condIdx]) / 
                               (tempMax[condIdx] - tempMin[condIdx]);
        
        // Add up to 0.15 bonus for warmer temperatures
        forecast.salesMultiplier += tempPercentile * 0.15;
    }
    
    return forecast;
}

// Displays the weather forecast and its potential business impact
void displayWeatherForecast(Weather& forecast) {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= WEATHER -=- FORECAST =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    cout << "     DAILY FORECAST" << endl;
    cout << "         Condition: " << forecast.condition << endl;
    cout << "       Temperature: " << forecast.temperature << " *C" << endl;
    space(1);
    
    // Displays business impact information
    cout << "  BUSINESS INSIGHTS" << endl;
    
    // Visual representation of expected customer traffic based on sales multiplier
    cout << "  Customer Traffic: ";
    int BarValue = (forecast.salesMultiplier * 10) / 2;
    cout << '[';
    displayFormat(BarValue, '*');

    for (int i = 0; i < 10 - BarValue; ++i) {
        cout << '-';
    }

    cout << ']';
    cout << endl;
    
    // Generate business recommendations based on forecast
    string recommendation;
    if (forecast.salesMultiplier > 1.2) {
        recommendation = "On demand! Stock up and prepare for a busy day.";
    } else if (forecast.salesMultiplier < 0.8) {
        recommendation = "Low turnout. Try discounts or promos to boost sales.";
    } else {
        recommendation = "Steady day ahead. Keep operations running smoothly.";
    }
    
    cout << "    Recommendation: " << recommendation << endl;
    space(1);

    // Store forecast data in the save file for later use
    currentSaveFile.plan.condition = forecast.condition;
    currentSaveFile.plan.temperature = forecast.temperature;
    
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ Press any key to continue... ]");
    
    _getch();
    playSFX("selectOption.wav", 30);
    displayDayPrepMenu();
}

// Allows the player to set the price for lemonade
// Shows break-even point and different profit margin options
void setPrice() {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= SET -=- PRICING =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);

    // Display pricing strategy suggestions with different margins
    cout << "       PRICING STRATEGY" << endl;
    cout << "      Break-even Price: $" << fixed << setprecision(2) << currentSaveFile.plan.price << endl;
    cout << "      Low Margin (10%): $" << fixed << setprecision(2) << currentSaveFile.plan.price * 1.1 << endl;
    cout << "   Medium Margin (50%): $" << fixed << setprecision(2) << currentSaveFile.plan.price * 1.5 << endl;
    cout << "    High Margin (100%): $" << fixed << setprecision(2) << currentSaveFile.plan.price * 2.0 << endl;
    space(1);
    
    displaySpacedFormat(72, '=');
    space(1);
    
    cout << "    Current Price: $" << fixed << setprecision(2) << currentSaveFile.plan.price << endl;
    cout << "  Enter New Price: $";
    
    // Get price input from user
    showCursor();
    cin >> currentSaveFile.plan.price;
    hideCursor();
    
    // Calculate profit estimate based on ingredients cost per cup
    // Formula considers the cost of each ingredient needed for one cup of lemonade
    currentSaveFile.plan.profitEstimate = currentSaveFile.plan.price - (
        ((LEMON_COST / 12) * 1.5) +    // Cost for 1.5 lemons per cup
        ((SUGAR_COST / 1000) * 25) +   // Cost for 25g of sugar per cup
        ((WATER_COST / 3785)) * 350 +  // Cost for 350ml of water per cup
        ((ICE_COST / 100)) * 2 +       // Cost for 2 ice cubes per cup
        (CUP_COST / 4)                // Cost of the cup itself (divided by 4 for singles)
    );

    cout << "    New Price Set: $" << fixed << setprecision(2) << currentSaveFile.plan.price << endl;
    cout << " Estimated Profit: $" << fixed << setprecision(2) << currentSaveFile.plan.profitEstimate << endl;
    
    space(1);
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ Press any key to continue... ]");
    
    _getch();
    playSFX("selectOption.wav", 30);
    displayDayPrepMenu();
}

// Creates a default day plan based on provided weather forecast
DayPlan generateDefaultPlan(const Weather& forecast) {
    DayPlan plan;

    plan.forecast = forecast;

    // Default marketing and expectations based on weather multiplier
    plan.marketingBudget = 0.0;
    plan.expectedCustomers = 10 * plan.forecast.salesMultiplier;

    // Calculating total ingredients needed for base number of customers (10)
    // These values establish the recipe for each cup of lemonade
    int totalWaterNeeded = 500 * 10;  // 500 mL per customer, for 10 customers
    int totalLemonSlicesNeeded = 3 * 10;  // 3 lemon slices per customer, for 10 customers
    int totalIceNeeded = 3 * 10;  // 3 ice cubes per customer, for 10 customers
    int totalCupsNeeded = 10;  // 1 cup per customer, for 10 customers
    int totalSugarNeeded = 40 * 10;  // 40g of sugar per customer, for 10 customers

    // Calculate costs for ingredients based on the base customer expectation    
    double lemonCost = totalLemonSlicesNeeded * LEMON_COST;
    double sugarCost = totalSugarNeeded * SUGAR_COST;
    double waterCost = totalWaterNeeded * WATER_COST;
    double iceCost = totalIceNeeded * ICE_COST;
    double cupCost = totalCupsNeeded * CUP_COST;

    // Calculate production cost per cup for profitability analysis
    double totalCostForIngredients = lemonCost + sugarCost + waterCost + iceCost;
    double productionCostPerCup = (totalCostForIngredients / totalCupsNeeded) + cupCost;

    // Profit estimate per cup
    double profitPerCup = currentSaveFile.plan.price - productionCostPerCup;
    double margin = (profitPerCup / productionCostPerCup) * 100;

    // Estimate the revenue and profit
    double revenue = currentSaveFile.plan.price * plan.expectedCustomers;
    double costs = productionCostPerCup * plan.expectedCustomers + plan.marketingBudget;
    plan.profitEstimate = revenue - costs;

    return plan;
}

// Generates a default day plan with weather-based initialization
DayPlan generateDefaultPlan() {

    // Generate random weather for the day
    Weather forecast = generateWeatherForecast();

    // Store weather data in the current save file
    currentSaveFile.plan.condition = forecast.condition;
    currentSaveFile.plan.temperature = forecast.temperature;

    // Generate a day plan based on the forecast
    return generateDefaultPlan(forecast);
}

// Displays the day plan screen with all relevant business metrics and inventory
// Shows expected customers, revenue, profit projections, and inventory levels
void displayDayPlan() {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= DAY -=- PLAN =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);

    // Calculate expected customers based on weather conditions
    // Base customer count - default number of customers regardless of conditions
    int baseCustomers = 10;
    
    // Initialize weather multiplier - will be adjusted based on conditions
    double weatherMultiplier = 1.0;
    
    // Apply condition-specific multipliers to customer traffic
    // Better weather = more customers, worse weather = fewer customers
    if (currentSaveFile.plan.condition == "Sunny") {
        weatherMultiplier = 1.5;
    } else if (currentSaveFile.plan.condition == "Partly Cloudy") {
        weatherMultiplier = 1.2;
    } else if (currentSaveFile.plan.condition == "Fair") {
        weatherMultiplier = 1.0;  // Neutral baseline
    } else if (currentSaveFile.plan.condition == "Cloudy") {
        weatherMultiplier = 0.7;
    } else if (currentSaveFile.plan.condition == "Stormy") {
        weatherMultiplier = 0.4;  // Worst case scenario
    }
    // Further adjust multiplier based on temperature
    // Hot weather increases demand for lemonade
    if (currentSaveFile.plan.temperature > 30) {
        weatherMultiplier += 0.2; // Hot weather increases demand
    } else if (currentSaveFile.plan.temperature < 20) {
        weatherMultiplier -= 0.1; // Cold weather decreases demand
    }
    
    // Calculate final customer count
    currentSaveFile.plan.expectedCustomers = static_cast<int>(baseCustomers * weatherMultiplier);
    
    // Ensure maxiumum is 15 customers
    if (currentSaveFile.plan.expectedCustomers > 15) {
        currentSaveFile.plan.expectedCustomers = 15;
    }
    
    // Calculate revenue and profit
    double estimatedRevenue = currentSaveFile.plan.price * currentSaveFile.plan.expectedCustomers;
    double estimatedProfit = currentSaveFile.plan.profitEstimate * currentSaveFile.plan.expectedCustomers;
    
    // Display business projections
    cout << "       DAILY PROJECTION" << endl;
    cout << "    Expected Customers: " << currentSaveFile.plan.expectedCustomers << endl;
    cout << "     Estimated Revenue: $" << fixed << setprecision(2) << estimatedRevenue<< endl;
    cout << "      Estimated Profit: $" << fixed << setprecision(2) << estimatedProfit << endl;
    space(2);

    cout << "                PRICING" << endl;
    cout << "                 Price: $" << currentSaveFile.plan.price << endl;
    cout << "      Estimated Profit: $" << fixed << setprecision(2) << currentSaveFile.plan.profitEstimate << endl;
    
    // Display current stocks
    goTo(36, 7); cout << "                 STOCKS" << endl;
    goTo(36, 8); cout << "                Lemons: " << currentSaveFile.stocks.lemons << " pcs. " << endl;
    goTo(36, 9); cout << "                 Sugar: " << currentSaveFile.stocks.sugar << " g" << endl;
    goTo(36, 10); cout << "                 Water: " << currentSaveFile.stocks.water << " mL" << endl;
    goTo(36, 11); cout << "                   Ice: " << currentSaveFile.stocks.ice << " cube/s" << endl;
    goTo(36, 12); cout << "                  Cups: " << currentSaveFile.stocks.cups << " pcs." << endl;

    // Display weather forecast
    goTo(36, 14); cout << "                WEATHER" << endl;
    goTo(36, 15); cout << "             Condition: " << currentSaveFile.plan.condition << endl;
    goTo(36, 16); cout << "           Temperature: " << currentSaveFile.plan.temperature << " *C" << endl;

    // Stock check
    bool sufficientStock = checkStockLevels();
    
    space(2);
    displaySpacedFormat(72, '#');
    space(1);

    // Display evaluation result based on stock check
    cout << "  EVALUATION: " << (sufficientStock ? "READY - Ready for the day!" : "INSUFFICIENT - Revise your strategies...") << endl;
    space(1);
    
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ Press any key to continue... ]");
    
    _getch();
    playSFX("selectOption.wav", 30);
    displayDayPrepMenu();
}

// Checks if current inventory is sufficient for expected sales
bool checkStockLevels() {
    /// Calculate total requirements based on recipe needs for 10 customers
    int totalWaterNeeded = 500 * 10;
    int totalLemonSlicesNeeded = 3 * 10;
    int totalIceNeeded = 3 * 10;
    int totalCupsNeeded = 10;
    int totalSugarNeeded = 40 * 10;

    // Compare current stock with total needs for the minimum viable business day
    return (currentSaveFile.stocks.lemons >= totalLemonSlicesNeeded &&
            currentSaveFile.stocks.sugar >= totalSugarNeeded &&
            currentSaveFile.stocks.water >= totalWaterNeeded &&
            currentSaveFile.stocks.ice >= totalIceNeeded &&
            currentSaveFile.stocks.cups >= totalCupsNeeded);
}

// Final confirmation screen before starting the sales day
// Gives warnings if inventory is insufficient and provides options to continue or return
void finalizeDayPrep() {
    clearScreen();
    displayHeader();
    space(1);
    
    centerText("READY TO START THE DAY?");
    space(2);
    
    // Check if player has enough stock for projected sales
    bool sufficientStock = checkStockLevels();
    
    if (!sufficientStock) { // Case 1: NOT ENOUGH STOCKS - Show warning
        cout << "  WARNING: You don't have enough supplies for your projected sales!" << endl;
        space(1);
        cout << "  OPTIONS:" << endl;
        cout << "    1. [ RETURN ] to purchase more supplies" << endl;
        cout << "    2.  [ START ] with current limited stock (may lead to lost sales)" << endl;
        space(1);
        
        displaySpacedFormat(72, '#');
        space(1);
        centerText("-= SELECT =-");
        
        goTo(1, 28);
        centerText("[ RETURN ]                [ START ]");

        // Cursor navigation logic for selection menu
        const int optionCount = 2;
        int x[optionCount] = { 19, 45 };
        int y[optionCount] = { 28, 28 };
        int current = 0;
        char key;
    
        // Menu selection loop - handles keyboard navigation
        while (true) {
            // Draw all cursors and option indicators
            for (int i = 0; i < optionCount; ++i) {
                // Draw ">>" at left of current option
                goTo(x[i] - 3, y[i]);
                cout << (i == current ? ">>" : "  ");
        
                // Erase previous "<<" at right if not the current option
                if (i != current) {
                    if (i == 0) moveCursor(0, 0, 13, 0);
                    else if (i == 1) moveCursor(0, 0, 12, 0);
                    cout << "  ";
                }
        
                // Draw "<<" at right for current option
                if (i == current) {
                    if (current == 0) moveCursor(0, 0, 13, 0);
                    else if (current == 1) moveCursor(0, 0, 12, 0);
                    cout << "<<";
                }
            }

            // Process keyboard input for menu navigation
            key = _getch();
            playSFX("navigateOption.wav", 30);
            if (key == 75) { // If 'Left Arrow' key is pressed
                current = (current - 1 + optionCount) % optionCount;
            } else if (key == 77) { // If 'Right Arrow' key is pressed
                current = (current + 1) % optionCount;
            } else if (key == 13) { // If 'Enter' key is pressed
                playSFX("selectOption.wav", 30);
                clearScreen();
                break;
            }
        }

        // Handle player's chice
        if (current == 0) {
            displayDayPrepMenu(); // Return to preparation menu
        } else if (current == 1) {
            // displayPreGameTransition();
            goToGameArea(); // Proceed to game play despite warnings
        }
    } else { // Case 2: ENOUGH STOCKS - Regular proceed options
        centerText("-= SELECT =-");
        
        goTo(1, 28);
        centerText("[ RETURN ]                [ START ]");

        // Same menu navigation logic as above
        const int optionCount = 2;
        int x[optionCount] = { 19, 45 };
        int y[optionCount] = { 28, 28 };
        int current = 0;
        char key;
    
        // Selection loop for keyboard indicators
        while (true) {
            // Draw all cursors and selection indicators
            for (int i = 0; i < optionCount; ++i) {
                // Draw ">>" at left
                goTo(x[i] - 3, y[i]);
                cout << (i == current ? ">>" : "  ");
        
                // Erase previous "<<" at right if not the current
                if (i != current) {
                    if (i == 0) moveCursor(0, 0, 13, 0);
                    else if (i == 1) moveCursor(0, 0, 12, 0);
                    cout << "  ";
                }
        
                // Draw "<<" at right for current option
                if (i == current) {
                    if (current == 0) moveCursor(0, 0, 13, 0);
                    else if (current == 1) moveCursor(0, 0, 12, 0);
                    cout << "<<";
                }
            }

            // Process keyboard input
            playSFX("navigateOption.wav", 30);
            key = _getch();
            if (key == 75) { // If 'Left Arrow' key is pressed
                current = (current - 1 + optionCount) % optionCount;
            } else if (key == 77) { // If 'Right Arrow' key is pressed
                current = (current + 1) % optionCount;
            } else if (key == 13) { // If 'Enter' key is pressed
                playSFX("selectOption.wav", 30);
                clearScreen();
                break;
            }
        }

        if (current == 0) {
            displayDayPrepMenu(); // Return to preparation menu
        } else if (current == 1) {
            // displayPreGameTransition();
            goToGameArea(); // Proceed to game play
        }
    }
}