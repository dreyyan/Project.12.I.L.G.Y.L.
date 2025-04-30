/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <string>
#include "prep.h"
#include "GUI.h"
#include "Utility.h"
using namespace std;
    
/*------------------- GLOBAL VARIABLES -------------------*/
const double LEMON_COST = 6.0 / 12.0;  // per pack(12 pcs.)
const double SUGAR_COST = 1.5 / 1000.0;  // per sugar bag(1kg)
const double WATER_COST = 1.0 / 3785.0; // per gallon(3785ml)
const double ICE_COST = 1.0 / 100.0; // per pack(100 cubes)
const double CUP_COST = 5.0 / 100.0;   // per pack(100 cups)

/*------------------- FUNCTION IMPLEMENTATIONS -------------------*/
void displayDayPrepMenu() {
    clearScreen();

    // Get data from json file
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
        cerr << "Could not open saveFiles.json\n";
        return;
    }

    json data;
    file >> data;

    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= DAY -=- PREPARATION =- ]");
    goTo(3, 3); cout << fixed << setprecision(2) << "$ " << currentSaveFile.financial_statistics.money;
    goTo(64, 3); cout << "DAY " << data[saveFileNum]["player_data"]["day"];
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    displayVLine(26, 5, 25, '#');
    goTo(0, 7);
    moveCursor(0, 0, 4, 0); cout << "[ RECIPES ";
    space(2);
    displaySpacedFormat(25, '=');
    space(1);
    moveCursor(0, 0, 4, 0); cout << "[ SUPPLIES";
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

    DayPlan plan = generateDefaultPlan();
    
    /*--------------------- START OF NAVIGATION ----------------------*/
    const int optionCount = 6;
    int x[optionCount] = {2, 2, 2, 2, 2, 2};
    int y[optionCount] = {7, 11, 15, 19, 23, 27};
    int current = 0;
    char key;
    
    while (true) {
        // Draw '>' cursor
        for (int i = 0; i < optionCount; ++i) {
            // Draw ">" at left
            goTo(x[i], y[i]);
            cout << (i == current ? ">" : " ");
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
    
    // Navigate to the selected option
    switch (current) {
        case 0:
            displayRecipeMenu();
            break;
        case 1:
            displaySupplyMenu();
            break;
        case 2: {
            Weather forecast = generateWeatherForecast();
            displayWeatherForecast(forecast);
            break;
        }
        case 3:
            setPrice(plan.recipe);
            break;
        case 4:
            displayDayPlan(plan);
            break;
        case 5:
            finalizeDayPrep(currentSaveFile, plan);
            break;
    }
    /*---------------------- END OF NAVIGATION -----------------------*/
}

/*------------------- UTILITY -------------------*/
void updateMessage(string message) {
    space(2);
    centerText(" + " + message + " updated successfully!");
    space(1);
}

void errorMessage(string message) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    centerText("ERROR: " + message);
}

void clearState() {
    space(1);
    errorMessage("Please enter a valid number");
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    goTo(1, 24); cout << "          ";
    goTo(1, 23);
}

void displayRecipeMenu() {
    Recipe currentRecipe = {2, 75, 3, 5.0, 1000}; // Default recipe

    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= RECIPE =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Lemons per Pitcher : " << currentRecipe.lemons << '\n';
    moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Sugar : " << currentRecipe.sugar << " g" << '\n';
    moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Water : " << currentRecipe.waterRatio << " mL" << '\n';
    moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Ice per Cup : " << currentRecipe.ice << '\n';
    space(1);
    
    displaySpacedFormat(72, '#');
    space(1);
    centerText("Adjust Recipe (A)     Save Recipe (S)     Load Recipe (L)     Back (B)");
    space(2);
    displaySpacedFormat(72, '#');
    
    char choice;
    do {
        choice = tolower(_getch());
        
        switch (choice) {
            case 'a':
                adjustRecipe(currentRecipe);
                break;
            case 's':
                saveRecipe(currentRecipe, "custom_recipe.dat");
                moveCursor(0, 6, 0, 0);
                centerText("Recipe Saved!");
                delayS(1);
                pressEnterToContinue();
                displayRecipeMenu();
                break;
            case 'l':
                currentRecipe = loadRecipe("custom_recipe.dat");
                moveCursor(0, 6, 0, 0);
                centerText("Recipe Loaded!");
                delayS(1);
                pressEnterToContinue();
                displayRecipeMenu();
                break;
            case 'b':
                displayDayPrepMenu();
                break;
        }
    } while (choice != 'b');
}

void adjustRecipe(Recipe& currentRecipe) {
    while (true) {
        clearScreen();
        displaySpacedFormat(72, '#');
        space(1);
        centerText("[ -= ADJUST -=- RECIPE =- ]");
        space(2);
        displaySpacedFormat(72, '#');
        space(1);
        
        moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Lemons per Pitcher : " << currentRecipe.lemons << '\n';
        moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Sugar : " << currentRecipe.sugar << " g" << '\n';
        moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Water : " << currentRecipe.waterRatio << " mL" << '\n';
        moveCursor(0, 0, 22, 0); cout << setw(21) << right << "Ice per Cup : " << currentRecipe.ice << '\n';
        space(1);
        
        displaySpacedFormat(72, '=');
        space(1);
        centerText("------ ADJUST ------");
        space(2);
        centerText("{ [1] Lemon -- [2] Sugar -- [3] Water -- [4] Ice/Cup }");
        space(2);
        centerText("{ [5] BACK }");
        space(2);
        displaySpacedFormat(72, '#');    
        space(1);
        
        char choice = _getch();
        int value;

        switch (choice) {
            case '1': {
                while (true) {
                    cout << " # of Lemons per Cup (1-10):\n";
                    cout << " " << currentRecipe.lemons << " >> ";
                    cin >> value;
                    
                    if (cin.fail()) clearState();
                    else break;
                }

                if (value >= 1 && value <= 10) {
                    currentRecipe.lemons = value;
                    updateMessage("# of lemons");
                } else errorMessage("Invalid # of lemons");
                break;
            }
            case '2': {
                while (true) {
                    cout << " g of Sugar per Cup (1-500g):\n";
                    cout << " " << currentRecipe.sugar << " >> ";
                    cin >> value;
        
                    if (cin.fail()) clearState();
                    else break;
                }

                if (value >= 1 && value <= 500) {
                    currentRecipe.sugar = value;
                    updateMessage("g of sugar");
                } else errorMessage("Invalid g of sugar");
                break;
            }
            case '3': {
                while (true) {}
                cout << " mL of Water per Cup (1-2000mL):\n";
                cout << " " << currentRecipe.waterRatio << " >> ";
                cin >> value;
    
                if (cin.fail()) clearState();
                else break;

                if (value >= 1 && value <= 2000) {
                    currentRecipe.waterRatio = value;
                    updateMessage("mL of water");
                } else errorMessage("Invalid mL of water");
                break;
            }
            case '4': {
                while (true) {
                    cout << " # of Ice Cubes per Cup (1-10):\n";
                    cout << " " << currentRecipe.sugar << " >> ";
                    cin >> value;
        
                    if (cin.fail()) clearState();
                    else break;
                }

                if (value >= 50 && value <= 500) {
                    currentRecipe.ice = value;
                    updateMessage("# of ice cubes");
                } else errorMessage("Invalid # of ice cubes");
                break;
            }
            case '5': {
                displayRecipeMenu();
                return;
                break;
            }
        }
        
        pressEnterToContinue();
    }
}

void displayRecipeStats(const Recipe& recipe) {
    space(1);
    displaySpacedFormat(72, '-');
    space(1);
    
    // Calculate recipe impacts
    double sourness = recipe.lemons * 2.5;
    double sweetness = recipe.sugar / 50.0 * 2.5;  
    double refreshment = (10 - abs(recipe.ice - 3)) * 1.0;
    double quality = (sourness + sweetness + refreshment) / 3.0;
    
    cout << "  Recipe Impact:" << endl;
    cout << "    Sourness: ";
    displayFormat(sourness, '*');
    cout << endl;
    
    cout << "    Sweetness: ";
    displayFormat(sweetness, '*');
    cout << endl;
    
    cout << "    Refreshment: ";
    displayFormat(refreshment, '*');
    cout << endl;
    
    cout << "    Overall Quality: " << fixed << setprecision(1) << quality << "/10.0" << endl;
    space(1);
    
    // Suggest price based on quality
    double suggestedPrice = 3.0 + (quality / 10.0) * 5.0;
    cout << "    Suggested Price: $" << fixed << setprecision(2) << suggestedPrice << endl;
}

void saveRecipe(Recipe& recipe, const char* recipeName) {
    // Would connect to file system in full implementation
    // cout << "Recipe saved as " << recipeName << "!" << endl;
}

Recipe loadRecipe(const char* recipeName) {
    // Would load from file system in full implementation
    Recipe defaultRecipe = {2, 100, 3, 5.0, 1000};
    // cout << "Loaded recipe: " << recipeName << endl;
    return defaultRecipe;
}

void displaySupplyMenu() {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= PURCHASE -=- SUPPLIES =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    // Display current stock and money
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

    int lemonsToAdd = 0, sugarToAdd = 0, waterToAdd = 0, iceToAdd = 0, cupsToAdd = 0;
    int lemonsIncrement = 12, sugarIncrement = 1000, waterIncrement = 3785, iceIncrement = 1000, cupsIncrement = 100;
    int lemonsQuantity = 1, sugarQuantity = 1, waterQuantity = 1, iceQuantity = 1, cupsQuantity = 1;
    double totalCost = 0.0;

    displayVLine(36, 5, 6, '#');
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

    // Cursor navigation logic
    const int optionCount = 5;
    int x[optionCount] = { 53, 53, 53, 53, 53 };
    int y[optionCount] = { 21, 22, 23, 24, 25 };
    int current = 0;
    int currentOption = 0;
    char key;

    SaveData data;
    SaveData &saveData = data;
  
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
            current = (current - 1 + optionCount) % optionCount;
            currentOption = current;
        } else if (key == 80) { // 'Down Arrow' key
            current = (current + 1) % optionCount;
            currentOption = current;
        } else if (key == 75) { // 'Left Arrow' key
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
        } else if (key == 77) { // 'Right Arrow' key
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
            // Separate block for regular keys like 'p' and 'b'
            char key1 = tolower(key);
            if (key1 == 'p') { // 'p' key
                if (saveData.financial_statistics.money) {
                    goTo(0, 29);
                    cout << "                                  ";
                    goTo(0, 29);
                    centerText("You don't have money!");
                    pressEnterToContinue();
                    displaySupplyMenu();
                } else if (totalCost == 0) {
                    continue;
                } else if (totalCost > saveData.financial_statistics.money) {
                    goTo(0, 29);
                    cout << "                                  ";
                    goTo(0, 29);
                    centerText("You don't have enough money!");
                    pressEnterToContinue();
                    displaySupplyMenu();
                    return;
                } else {
                    // Update stocks and money
                    saveData.stocks.lemons += lemonsToAdd;
                    saveData.stocks.sugar += sugarToAdd;
                    saveData.stocks.water += waterToAdd;
                    saveData.stocks.ice += iceToAdd;
                    saveData.stocks.cups += cupsToAdd;
                    saveData.financial_statistics.money -= totalCost;
                    saveData.financial_statistics.expenses += totalCost;
                    centerText("Purchase complete!");
                    pressEnterToContinue();
                    displaySupplyMenu();
                }
            } else if (key1 == 'b') { // 'b' key
                displayDayPrepMenu();
            }
        }

        goTo(59, 7);
        cout << "      ";
    
        goTo(59, 7);
        cout << totalCost;
    }
}

Weather generateWeatherForecast() {
    // Simple random weather generation
    Weather forecast;
    
    const std::string conditions[] = {"Sunny", "Partly Cloudy", "Cloudy", "Rainy", "Stormy"};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> condDist(0, 4);
    uniform_int_distribution<> tempDist(15, 40);
    
    int condIdx = condDist(gen);
    forecast.condition = conditions[condIdx];
    forecast.temperature = tempDist(gen);
    
    // Set sales multiplier based on conditions
    double multipliers[] = {1.5, 1.2, 1.0, 0.7, 0.4};
    forecast.salesMultiplier = multipliers[condIdx];
    
    // Adjust for temperature
    if (forecast.temperature > 30) {
        forecast.salesMultiplier += 0.3;
    } else if (forecast.temperature < 20) {
        forecast.salesMultiplier -= 0.2;
    }
    
    return forecast;
}

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
    
    // Business impact
    cout << "  BUSINESS INSIGHTS" << endl;
    
    cout << "  Customer Traffic: ";
    int BarValue = (forecast.salesMultiplier * 10) / 2;
    cout << '[';
    displayFormat(BarValue, '*');

    for (int i = 0; i < 10 - BarValue; ++i) {
        cout << '-';
    }

    cout << ']';
    cout << endl;
    
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
    
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[Press any key to continue...]");
    
    _getch();
    displayDayPrepMenu();
}

void setPrice(Recipe& recipe) {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= SET -=- PRICING =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    // Calculate production cost
    double lemonCost = recipe.lemons * LEMON_COST;
    double sugarCost = recipe.sugar * SUGAR_COST;
    double waterCost = recipe.waterRatio * WATER_COST;
    double iceCost = recipe.ice * ICE_COST;
    double cupCost = CUP_COST;
    
    double costPerPitcher = lemonCost + sugarCost + waterCost;
    int cupsPerPitcher = recipe.waterRatio / 250; // Assuming 250mL per cup
    double productionCostPerCup = (costPerPitcher / cupsPerPitcher) + iceCost + cupCost;
    
    // Display costs
    cout << "       PRODUCTION COSTS" << endl;
    cout << "      Cost per Pitcher: $" << fixed << setprecision(2) << costPerPitcher << endl;
    cout << "          Cost per Cup: $" << fixed << setprecision(2) << productionCostPerCup << endl;
    cout << "      Cups per Pitcher: " << cupsPerPitcher << endl;
    space(1);
    
    // Display pricing strategy
    cout << "       PRICING STRATEGY" << endl;
    cout << "      Break-even Price: $" << fixed << setprecision(2) << productionCostPerCup << endl;
    cout << "      Low Margin (10%): $" << fixed << setprecision(2) << productionCostPerCup * 1.1 << endl;
    cout << "   Medium Margin (50%): $" << fixed << setprecision(2) << productionCostPerCup * 1.5 << endl;
    cout << "    High Margin (100%): $" << fixed << setprecision(2) << productionCostPerCup * 2.0 << endl;
    space(1);
    
    displaySpacedFormat(72, '=');
    space(1);
    
    cout << "    Current Price: $" << fixed << setprecision(2) << recipe.price << endl;
    cout << "  Enter New Price: $";
    
    showCursor();
    cin >> recipe.price;
    hideCursor();
    
    // Display profit margins
    space(1);
    double profitPerCup = recipe.price - productionCostPerCup;
    double margin = (profitPerCup / productionCostPerCup) * 100;
    
    cout << "    New Price Set: $" << fixed << setprecision(2) << recipe.price << endl;
    cout << "   Profit per Cup: $" << fixed << setprecision(2) << profitPerCup << endl;
    cout << "    Profit Margin: " << fixed << setprecision(1) << margin << "%" << endl;
    
    space(1);
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[Press any key to continue...]");
    
    _getch();
    displayDayPrepMenu();
}

DayPlan generateDefaultPlan() {
    DayPlan plan;
    
    // Default recipe
    plan.recipe = {2, 100, 3, 5.0, 1000};
    
    // Weather forecast
    plan.forecast = generateWeatherForecast();
    
    // Default marketing and expectations
    plan.marketingBudget = 0.0;
    plan.expectedCustomers = 30 * plan.forecast.salesMultiplier;
    
    // Profit estimate
    double lemonCost = plan.recipe.lemons * LEMON_COST;
    double sugarCost = plan.recipe.sugar * SUGAR_COST;
    double waterCost = plan.recipe.waterRatio * WATER_COST;
    double iceCost = plan.recipe.ice * ICE_COST;
    double cupCost = CUP_COST;

    double costPerPitcher = lemonCost + sugarCost + waterCost;
    int cupsPerPitcher = plan.recipe.waterRatio / 250;

    double productionCostPerCup = (costPerPitcher / cupsPerPitcher) + iceCost + cupCost;
    
    double profitPerCup = plan.recipe.price - productionCostPerCup;
    double margin = (profitPerCup / productionCostPerCup) * 100;

    double revenue = plan.recipe.price * plan.expectedCustomers;
    double costs = productionCostPerCup * plan.expectedCustomers + plan.marketingBudget;
    plan.profitEstimate = revenue - costs;    
    
    return plan;
}

void displayDayPlan(const DayPlan& plan) {
    clearScreen();
    displaySpacedFormat(72, '#');
    space(1);
    centerText("[ -= DAY -=- PLAN =- ]");
    space(2);
    displaySpacedFormat(72, '#');
    space(1);
    
    // Recipe summary
    cout << "                 RECIPE" << endl;
    cout << "    Lemons per Pitcher: " << plan.recipe.lemons << endl;
    cout << "                 Sugar: " << plan.recipe.sugar << " grams" << endl;
    cout << "                 Water: " << plan.recipe.waterRatio << " mL" << endl;
    cout << "           Ice per Cup: " << plan.recipe.ice << " cubes" << endl;
    cout << "         Price per Cup: $" << fixed << setprecision(2) << plan.recipe.price << endl;
    space(1);
    
    // Weather forecast
    cout << "                WEATHER" << endl;
    cout << "             Condition: " << plan.forecast.condition << endl;
    cout << "           Temperature: " << plan.forecast.temperature << " *C" << endl;
    space(1);
    
    // Business projections
    cout << "       DAILY PROJECTION" << endl;
    cout << "    Expected Customers: " << static_cast<int>(plan.expectedCustomers) << endl;
    cout << "     Estimated Revenue: $" << fixed << setprecision(2) << (plan.recipe.price * plan.expectedCustomers) << endl;
    cout << "      Estimated Profit: $" << fixed << setprecision(2) << plan.profitEstimate << endl;
    space(1);
    
    displaySpacedFormat(72, '#');
    space(1);

    // Stock check
    bool sufficientStock = checkStockLevels(currentSaveFile, plan.recipe, static_cast<int>(plan.expectedCustomers));
    
    cout << "  EVALUATION: " << (sufficientStock ? "READY - Ready for the day!" : "INSUFFICIENT - Revise your strategies...") << endl;
    space(1);
    
    displaySpacedFormat(72, '#');
    space(1);
    centerText("Press any key to return to menu");
    
    _getch();
    displayDayPrepMenu();
}

bool checkStockLevels(const SaveData& saveData, const Recipe& recipe, int expectedCups) {
    // Calculate required ingredients for expected sales
    int cupsPerPitcher = recipe.waterRatio / 250;
    int pitchersNeeded = (expectedCups + cupsPerPitcher - 1) / cupsPerPitcher; // Round up
    
    int lemonsNeeded = pitchersNeeded * recipe.lemons;
    int sugarNeeded = pitchersNeeded * recipe.sugar;
    int waterNeeded = pitchersNeeded * recipe.waterRatio;
    int iceNeeded = expectedCups * recipe.ice;
    int cupsNeeded = expectedCups;
    
    // Check if current stock is sufficient
    return (saveData.stocks.lemons >= lemonsNeeded &&
            saveData.stocks.sugar >= sugarNeeded &&
            saveData.stocks.water >= waterNeeded &&
            saveData.stocks.ice >= iceNeeded &&
            saveData.stocks.cups >= cupsNeeded);
}

void finalizeDayPrep(SaveData& saveData, DayPlan& plan) {
    clearScreen();
    displayHeader();
    space(1);
    
    centerText("READY TO START THE DAY?");
    space(1);
    displaySpacedFormat(72, '-');
    space(1);
    
    // Final checks and warnings
    bool sufficientStock = checkStockLevels(saveData, plan.recipe, static_cast<int>(plan.expectedCustomers));
    
    if (!sufficientStock) {
        cout << "  WARNING: You don't have enough supplies for your projected sales!" << endl;
        space(1);
        cout << "  Options:" << endl;
        cout << "    1. Return to purchase more supplies" << endl;
        cout << "    2. Continue with limited stock (may result in lost sales)" << endl;
        space(1);
        
        displaySpacedFormat(72, '-');
        space(1);
        centerText("Select option: ");
        
        char choice = _getch();
        if (choice == '1') {
            displaySupplyMenu();
            return;
        }
    }
    
    // Display final confirmation
    cout << "  Today's Plan:" << endl;
    cout << "    Recipe: " << plan.recipe.lemons << " lemons, " << plan.recipe.sugar << "g sugar, " 
         << plan.recipe.waterRatio << "mL water, " << plan.recipe.ice << " ice/cup" << endl;
    cout << "    Price: $" << fixed << setprecision(2) << plan.recipe.price << " per cup" << endl;
    cout << "    Weather: " << plan.forecast.condition << ", " << plan.forecast.temperature << "°C" << endl;
    cout << "    Expected Customers: " << static_cast<int>(plan.expectedCustomers) << endl;
    cout << "    Projected Profit: $" << fixed << setprecision(2) << plan.profitEstimate << endl;
    space(1);
    
    displaySpacedFormat(72, '-');
    space(1);
    centerText("Start the Day? (Y/N)");
    
    char confirm = tolower(_getch());
    if (confirm == 'y') {
        // Here you would implement the day simulation
        // This would involve consuming resources, generating customers
        // and updating the player's financial stats
        
        centerText("Starting the day...");
        delayMs(1000); // Simulate processing
        
        // This would be where call a function to actually run the day's simulation
        goToGameArea();
    } else {
        displayDayPrepMenu();
    }
}