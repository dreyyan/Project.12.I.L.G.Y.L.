/*----------------------- HEADER FILES -----------------------*/
#include <conio.h> // _getch()
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

#include "prep.h"
#include "Station.h"
#include "Portfolio.h"
#include "GUI.h"
#include "Scenes.h"
#include "Utility.h"
using namespace std;

void daySummary() {
    // UPDATES
    currentSaveFile.player_data.day += 1;

    clearScreen();
    goTo(1, 1);
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("DAY SUMMARY"); space(2);
    displayBlockFormat(72, 1, '#'); space(2);

    goTo(1, 28);
    centerText("Press 'Enter' to continue..."); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);
}

void customerEvaluation(Customer& customer) {
    double percentage;

    clearScreen();
    goTo(1, 1);
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("EVALUATION"); space(2);
    displayBlockFormat(72, 1, '#'); space(2);

    moveCursor(0, 0, 10, 0); cout << "Customer Number: " << customer.customerNumber; space(1);
    moveCursor(0, 0, 10, 0); cout << "Name: " << customer.name; space(2);

    moveCursor(0, 0, 10, 0); cout << "Cup Size: " << customer.cupSize; space(1);
    moveCursor(0, 0, 10, 0); cout << "Lemon Slices: " << customer.slices; space(1);
    moveCursor(0, 0, 10, 0); cout << "Sugar Level: " << customer.sugarLevel; space(1);
    moveCursor(0, 0, 10, 0); cout << "Ice: " << customer.iceAmount; space(2);

    moveCursor(0, 0, 10, 0); cout << "Preparation Satisfaction: " << customer.preparationSatisfaction << "%"; space(1);
    moveCursor(0, 0, 10, 0); cout << "Mixing Satisfaction: " << customer.mixingSatisfaction << "%"; space(1);
    moveCursor(0, 0, 10, 0); cout << "Serving Satisfaction: " << customer.servingSatisfaction << "%"; space(3);

    displayBlockFormat(72, 1, '#'); space(2);

    percentage = (customer.preparationSatisfaction + customer.mixingSatisfaction + customer.servingSatisfaction) / 3.0;
    moveCursor(0, 0, 10, 0); cout << "[ TOTAL ]: " << percentage << '%'; space(2);

    // Needs Fix: 
    currentSaveFile.financial_statistics.money += currentSaveFile.plan.price * (percentage / 100.0);

    goTo(1, 28);
    centerText("Press 'Enter' to continue..."); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);
}

void servingStation(Customer& customer) {
    clearScreen();
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("      PREPARATION                MIXING               [SERVING]        ");
    space(2);
    displayBlockFormat(72, 1, '='); space(1);
    centerText("[ -= SERVING -=- STATION =- ]");
    space(2);
    displayBlockFormat(72, 1, '#'); space(1);

    centerText("-= SERVE-IT! =-");
    space(1);
    centerText("Press 'Enter' to finish order"); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);
;
    // PLACEHOLDER(Remove after debug)
    int minigame4Score = 100;

    // Save score
    customer.servingSatisfaction = minigame4Score;

    centerText("Order finished!"); delayS(2); space(2);
    customerEvaluation(customer);
}

void mixingStation(Customer& customer) {
    clearScreen();
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("      PREPARATION               [MIXING]                SERVING        ");
    space(2);
    displayBlockFormat(72, 1, '='); space(1);
    centerText("[ -= MIXING -=- STATION =- ]");
    space(2);
    displayBlockFormat(72, 1, '#'); space(1);

    // MINIGAME 3: MIX MIX MIX!
    centerText("-= MIX MIX MIX! =-");
    space(1);
    centerText("Press 'Enter' to mix!"); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);

    srand(static_cast<unsigned>(time(0)));  // Random seed based on time
    int score3 = 0;
    int minigame3Score = 0;

    // Define the messages and the corresponding tasks
    string messages[] = {
        "[ 0% ] Getting glass and lemons ready...",
        "[ 25% ] Squeezing lemons...",
        "[ 50% ] Pouring water...",
        "[ 75% ] Mixing sugar and ice...",
        "[ 100% ] Lemonade done!"
    };

    // Randomize key sequence for WASD
    char keys[] = {'W', 'A', 'S', 'D'};
    
    // Loop through each message and ask the player to press a random key
    for (int i = 0; i < 5; ++i) {
        char targetKey = keys[rand() % 4]; // Randomly select W, A, S, or D

        // Display message
        centerText(messages[i]);
        space(1);
        
        // Show prompt for the user to press the correct key
        centerText("Press the " + string(1, targetKey) + " key NOW!"); space(1);

        // Wait for the user input and measure the time
        auto start = chrono::steady_clock::now();
        char input = toupper(_getch()); // Capture user input
        auto end = chrono::steady_clock::now();
        
        // Check if the key pressed matches the target key
        if (input == targetKey) {
            double reactionTime = chrono::duration<double>(end - start).count();
            if (reactionTime <= 1.0) {
                centerText("Perfect timing! +20%"); space(1);
                score3 = 20;
            } else {
                centerText("Good, but a little slow. +10%"); space(1);
                score3 = 10;
            }
        } else {
            centerText("Oops! Wrong key. +0%"); space(1);
        }

        minigame3Score += score3;

        // Short pause before next round
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Save score
    customer.mixingSatisfaction = minigame3Score;

    // Proceed to the next station
    goTo(1, 29);
    centerText("Press 'Enter' to continue..."); 
    char key2;
    do {
        key2 = _getch();
        if (key2 == 13) {
            servingStation(customer);
        }
    } while (key2 != 13);
}

void preparationStation(Customer& customer) {
    bool canServeCustomer = true;

    // 1. Convert needed stocks
    int sugarNeeded = 0;
    if (customer.sugarLevel == "0%") sugarNeeded = 0;
    else if (customer.sugarLevel == "25%") sugarNeeded = 10;
    else if (customer.sugarLevel == "50%") sugarNeeded = 20;
    else if (customer.sugarLevel == "75%") sugarNeeded = 3;
    else if (customer.sugarLevel == "100%") sugarNeeded = 40;

    int iceNeeded = 0;
    if (customer.iceAmount == "None") iceNeeded = 0;
    else if (customer.iceAmount == "Less Ice") iceNeeded = 1;
    else if (customer.iceAmount == "Regular") iceNeeded = 2;
    else if (customer.iceAmount == "Extra Ice") iceNeeded = 3;

    int waterNeeded = 0;
    if (customer.cupSize == "Small") waterNeeded = 200;
    else if (customer.cupSize == "Medium") waterNeeded = 350;
    else if (customer.cupSize == "Large") waterNeeded = 500;

    // 2. Check if stocks are enough
    if (currentSaveFile.stocks.lemons < customer.slices) canServeCustomer = false;
    if (currentSaveFile.stocks.water < waterNeeded) canServeCustomer = false;
    if (currentSaveFile.stocks.sugar < sugarNeeded) canServeCustomer = false;
    if (currentSaveFile.stocks.cups < 1) canServeCustomer = false;
    if (currentSaveFile.stocks.ice < iceNeeded) canServeCustomer = false;

    if (!canServeCustomer) {
        goTo(1, 1);
        displayBlockFormat(72, 30, ' ');
        goTo(1, 1);
        displayBlockFormat(72, 1, '#'); space(1);
        centerText("CANNOT SERVE CUSTOMER: Insufficient Stocks"); space(2);
        displayBlockFormat(72, 1, '#'); space(2);
        goTo(1, 29);
        centerText("Press 'Enter' to continue..."); 
        char key;
        do {
            key = _getch();
        } while (key != 13);
        return;
    }

    // 3. Update stocks
    currentSaveFile.stocks.lemons -= customer.slices;
    currentSaveFile.stocks.water -= waterNeeded;
    currentSaveFile.stocks.sugar -= sugarNeeded;
    currentSaveFile.stocks.cups -= 1;
    currentSaveFile.stocks.ice -= iceNeeded;

    // MINIGAME 1: CATCH THE LEMON
    clearScreen();
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("      [PREPARATION]              MIXING                 SERVING        ");
    space(2);
    displayBlockFormat(72, 1, '='); space(1);
    centerText("[ -= PREPARATION -=- STATION =- ]");
    space(2);
    displayBlockFormat(72, 1, '#'); space(1);

    centerText("-= CATCH -=- THE -=- LEMON! =-");
    space(1);
    centerText("Press the appropriate key at the right time!"); space(2);
    
    int score1 = 0;
    int minigame1Score = 0;

    srand(time(0));

    for (int i = 0; i < customer.slices; i++) {
        char targetKey = 'A' + rand() % 26; // Random letter from A to Z
    
        int delaySeconds = 1 + rand() % 5;
        this_thread::sleep_for(chrono::seconds(delaySeconds));
    
        centerText("PRESS " + string(1, targetKey) + " NOW!"); space(1);
        auto start = chrono::steady_clock::now();
    
        char input = toupper(_getch());
        auto end = chrono::steady_clock::now();
        double reactionTime = chrono::duration<double>(end - start).count();
    
        if (input == targetKey) {
            if (reactionTime <= 1.0) {
                centerText("Perfect! 100%"); space(2);
                score1 = 100;
            } else {
                // Calculate score based on reaction time
                score1 = static_cast<int>(100 - (reactionTime - 1.0) * 40);
                if (score1 < 10) score1 = 10; // Minimum score1
                centerText("Too slow... " + to_string(score1) + "%"); space(2);
            }
        } else {
            centerText("Wrong key! 0%"); space(2);
            score1 = 0;
        }
        minigame1Score += score1;
    }

    minigame1Score /= customer.slices;

    // Proceed to the next minigame
    goTo(1, 29);
    centerText("Press 'Enter' to continue..."); 
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);

    // CLEAR
    goTo(1, 29);
    displayBlockFormat(72, 1, ' ');

    goTo(1, 11);
    displayBlockFormat(72, 18, ' ');
    goTo(1, 11);
    
    // MINIGAME 2: SUGAR RUSH!
    centerText("-= SUGAR -=- RUSH! =-");
    space(1);
    centerText("Select the customer's preferred sugar level:"); space(2);
    centerText("[1] 0% | [2] 25% | [3] 50% | [4] 75% | [5] 100%"); space(1);

    int score2 = 0;
    int minigame2Score = 0;

    vector<string> sugarLevels = {"0%", "25%", "50%", "75%", "100%"};

    char input = _getch();  // wait for key press
    int index = input - '1';  // convert char '1'-'5' to index 0-4

    if (index >= 0 && index < sugarLevels.size()) {
        string chosenLevel = sugarLevels[index];
        space(1);
        centerText("You chose: " + chosenLevel);
        space(1);

        if (chosenLevel == customer.sugarLevel) {
            centerText("Perfect match!");
            score2 = 100;
        } else {
            // Calculate closeness by index difference
            int customerIndex = find(sugarLevels.begin(), sugarLevels.end(), customer.sugarLevel) - sugarLevels.begin();
            int diff = abs(customerIndex - index);
            score2 = max(0, 100 - diff * 25);  // Lose 25% per step off
            centerText("Close, but not exact... " + to_string(score2) + "%");
        }
    } else {
        centerText("Invalid input! 0%");
        score2 = 0;
    }

    minigame2Score += score2;
    
    // Save scores
    customer.preparationSatisfaction = (minigame1Score + minigame2Score) / 2;

    // Proceed to the next station
    goTo(1, 29);
    centerText("Press 'Enter' to continue...");
    char key2;
    do {
        key2 = _getch();
        if (key2 == 13) {
            // CLEAR
            goTo(1, 29);
            displayBlockFormat(72, 1, ' ');

            mixingStation(customer);
        }
    } while (key2 != 13);
}

string generateRandomName() {
    vector<string> names = {"Alex", "Chris", "Taylor", "Jordan", "Jamie", "Morgan", "Casey", "Riley", "Sam", "Charlie"};
    return names[rand() % names.size()];
}

void saveCustomerData(const Customer& customer) {
    ofstream outFile("orders.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "Customer #" << customer.customerNumber << ": " << customer.name << "\n";
        outFile << "     Slices: " << customer.slices << "\n";
        outFile << "   Cup Size: " << customer.cupSize << "\n";
        outFile << "Sugar Level: " << customer.sugarLevel << "\n";
        outFile << " Ice Amount: " << customer.iceAmount << "\n";
        outFile << fixed << setprecision(2);
        outFile << "##############################\n";
        outFile.close();
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

void displayOrderNotification(const Customer& customer) {
    goTo(14, 21);
    cout << "A CUSTOMER HAS ARRIVED!";

    goTo(12, 22);
    cout << "Press 'Enter' to TAKE ORDER";

    goTo(14, 24);
    cout << "CUSTOMER #" + to_string(customer.customerNumber) + " - " + customer.name;
    goTo(14, 25);
    cout << "      Slices: " << customer.slices;
    goTo(14, 26);
    cout << "    Cup Size: " + customer.cupSize;
    goTo(14, 27);
    cout << " Sugar Level: " + customer.sugarLevel;
    goTo(14, 28);
    cout << "  Ice Amount: " + customer.iceAmount;
    space(2);
}