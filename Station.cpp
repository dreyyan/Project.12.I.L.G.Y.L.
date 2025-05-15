/*----------------------- HEADER FILES -----------------------*/
#include <conio.h>      // _getch()
#include <iomanip> 
#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>       // For dynamic arrays
#include <random>       // For random number generation
#include <chrono>       // For timing functions
#include <thread>       // For sleep and thread management
#include <windows.h>    // For Windows console functions (COORD, HANDLE, etc.)

#include "prep.h" 
#include "Station.h" 
#include "Portfolio.h" 
#include "GUI.h" 
#include "Scenes.h" 
#include "Utility.h" 
using namespace std;

// Performs a skill check minigame where player must time a spacebar press
int performSkillCheck(int difficulty) {
    // Save current cursor position to restore later
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD originalPos = csbi.dwCursorPosition;
    
    const int BAR_WIDTH = 30;
    int SUCCESS_START, SUCCESS_END;

    // Adjust difficulty by changing the success zone size
    switch (difficulty) {
        case 1: // Easy - larger success zone
            SUCCESS_START = 8;
            SUCCESS_END = 22;
            break;
        case 2: // Medium - medium success zone
            SUCCESS_START = 10;
            SUCCESS_END = 20;
            break;
        case 3: // Hard - smaller success zone
            SUCCESS_START = 12;
            SUCCESS_END = 18;
            break;
        default: // Default to medium if invalid difficulty provided
            SUCCESS_START = 10;
            SUCCESS_END = 20;
    }
    
    int pos = 0; // Starting position of the marker
    int direction = 1; // Direction of marker movement (1=right, -1=left)
    bool running = true;

    // Coordinates for the top-left corner of the bar
    const short startX = 19;
    const short startY = 13;

    // Function to draw the skill check bar and moving arrow
    auto drawBar = [=](int pos) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        // Top border
        SetConsoleCursorPosition(hConsole, {startX, startY});
        cout << "+";
        for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
        cout << "+";

        // Success zone bar - vertical bars represent the success zone
        SetConsoleCursorPosition(hConsole, {startX, (short)(startY + 1)});
        cout << "|";
        for (int i = 0; i < BAR_WIDTH; i++) {
            if (i >= SUCCESS_START && i <= SUCCESS_END) cout << "|"; // success zone
            else cout << " ";
        }
        cout << "|";

        // Bottom border
        SetConsoleCursorPosition(hConsole, {startX, (short)(startY + 2)});
        cout << "+";
        for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
        cout << "+";

        // Arrow line (overwrite old one)
        SetConsoleCursorPosition(hConsole, {startX, (short)(startY + 3)});
        for (int i = 0; i < BAR_WIDTH + 2; i++) cout << " ";
        SetConsoleCursorPosition(hConsole, {(short)(startX + 1 + pos), (short)(startY + 3)});
        cout << "^"; // Draw the arrow at current position
    };

    COORD skillCheckPos = {startX, startY};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), skillCheckPos);

     // Main skill check loop
    while (running) {
        drawBar(pos);

        // Check for spacebar press
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                running = false;
                break;
            }
        }

        // Move the position and bounce at the edges
        pos += direction;
        if (pos >= BAR_WIDTH - 1 || pos <= 0) direction *= -1;

        // Change speed: faster inside success zone for increased difficulty
        if (pos >= SUCCESS_START && pos <= SUCCESS_END)
            Sleep(1);
        else
            Sleep(5);
    }

    // Calculate the success percentage based on distance from success zone
    int distanceFromSuccessZone = 0;
    if (pos < SUCCESS_START)
        distanceFromSuccessZone = SUCCESS_START - pos;
    else if (pos > SUCCESS_END)
        distanceFromSuccessZone = pos - SUCCESS_END;

    int successPercentage = 100 - ((distanceFromSuccessZone * 100) / (BAR_WIDTH / 2));
    if (successPercentage < 0) successPercentage = 0;
    if (successPercentage > 100) successPercentage = 100;

    return successPercentage;
}

// Shows the end-of-day summary and updates game statistics
void daySummary() {
    // Update statistics - increment day count
    currentSaveFile.player_data.day += 1;

    // Display day summary screen
    clearScreen();
    goTo(1, 1);
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("DAY SUMMARY"); space(2);
    displayBlockFormat(72, 1, '#'); space(2);

    // Display financial information
    centerText("FINANCIAL STATISTICS");
    cout << "                              Money: $" << fixed << setprecision(2) << currentSaveFile.financial_statistics.money << endl;
    cout << "                            Revenue: $" << fixed << setprecision(2) << currentSaveFile.financial_statistics.revenue << endl;
    cout << "                           Expenses: $" << fixed << setprecision(2) << currentSaveFile.financial_statistics.expenses << endl;
    cout << "                              Price: $" << fixed << setprecision(2) << currentSaveFile.plan.price; space(2);

    // Display remaining inventory
    centerText("STOCKS REMAINING");
    cout << "                             Lemons: " << fixed << setprecision(2) << currentSaveFile.stocks.lemons << endl;
    cout << "                              Water: " << fixed << setprecision(2) << currentSaveFile.stocks.water << endl;
    cout << "                              Sugar: " << fixed << setprecision(2) << currentSaveFile.stocks.sugar << endl;
    cout << "                                Ice: " << fixed << setprecision(2) << currentSaveFile.stocks.ice << endl;
    cout << "                               Cups: " << fixed << setprecision(2) << currentSaveFile.stocks.cups; space(2);

    centerText("Today was a long day...");

    // Wait for user to continue
    goTo(1, 28);
    centerText("Press 'Enter' to continue..."); space(2);
    char key1;
    do {
        key1 = _getch();
        startGame();  // Start next day
    } while (key1 != 13);
}

// Shows customer order evaluation and calculate profits
void customerEvaluation(Customer& customer) {
    double percentage;

    // Display evaluation screen
    clearScreen();
    goTo(1, 1);
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("EVALUATION"); space(2);
    displayBlockFormat(72, 1, '#'); space(2);

    // Show customer information
    moveCursor(0, 0, 10, 0); cout << "Customer Number: " << customer.customerNumber; space(1);
    moveCursor(0, 0, 10, 0); cout << "Name: " << customer.name; space(2);

    // Show order details
    moveCursor(0, 0, 10, 0); cout << "Cup Size: " << customer.cupSize; space(1);
    moveCursor(0, 0, 10, 0); cout << "Lemon Slices: " << customer.slices; space(1);
    moveCursor(0, 0, 10, 0); cout << "Sugar Level: " << customer.sugarLevel; space(1);
    moveCursor(0, 0, 10, 0); cout << "Ice: " << customer.iceAmount; space(2);

    // Show satisfaction metrics
    moveCursor(0, 0, 10, 0); cout << "Preparation Satisfaction: " << customer.preparationSatisfaction << "%"; space(1);
    moveCursor(0, 0, 10, 0); cout << "Mixing Satisfaction: " << customer.mixingSatisfaction << "%"; space(1);
    moveCursor(0, 0, 10, 0); cout << "Serving Satisfaction: " << customer.servingSatisfaction << "%"; space(3);

    displayBlockFormat(72, 1, '#'); space(2);

    // Calculate average satisfaction percentage
    percentage = (customer.preparationSatisfaction + customer.mixingSatisfaction + customer.servingSatisfaction) / 3.0;

    // Calculate money earned based on satisfaction
    double moneyEarned = currentSaveFile.plan.price * (percentage / 100.0);
    
    // Update financial statistics
    currentSaveFile.financial_statistics.money += moneyEarned;
    currentSaveFile.financial_statistics.revenue += moneyEarned;

    // Display final results
    moveCursor(0, 0, 10, 0); cout << " [ TOTAL SCORE ]: " << percentage << '%'; space(1);
    moveCursor(0, 0, 10, 0); cout << "[ TOTAL PROFIT ]: $" << moneyEarned;

    // Wait for user to continue
    goTo(1, 28);
    centerText("Press 'Enter' to continue..."); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);
}

// Final staton for serving lemonade
void servingStation(Customer& customer) {
    // Dsiaplay serving station screen
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

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());

    // Define the difficulty range (1 to 3)
    uniform_int_distribution<> dis(1, 3);

    centerText("Press [SPACE] to stop the indicator inside the success zone!"); space(2);

    // MINIGAME #4: Serve-It! - Timing-based minigame
    int successPercentage = performSkillCheck(dis(gen));

    int minigame4Score = successPercentage;

    // Save score to customer object
    customer.servingSatisfaction = minigame4Score;

    // Proceed to customer evaluation
    customerEvaluation(customer);
}

// Mixing station for making the lemonade
void mixingStation(Customer& customer) {
    // Display mixing station screen
    clearScreen();
    displayBlockFormat(72, 1, '#'); space(1);
    centerText("      PREPARATION               [MIXING]                SERVING        ");
    space(2);
    displayBlockFormat(72, 1, '='); space(1);
    centerText("[ -= MIXING -=- STATION =- ]");
    space(2);
    displayBlockFormat(72, 1, '#'); space(1);

    // MINIGAME 3: MIX MIX MIX! - Reaction time minigame
    centerText("-= MIX MIX MIX! =-");
    space(1);
    centerText("Press 'Enter' to mix!"); space(2);
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);

    // Initialize random seed
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
    
    // Loop through each mixing step
    for (int i = 0; i < 5; ++i) {
        char targetKey = keys[rand() % 4]; // Randomly select W, A, S, or D

        // Display message (current mixing step)
        centerText(messages[i]);
        space(1);
        
        // Show prompt for the user to press the correct key
        centerText("Press the " + string(1, targetKey) + " key NOW!"); space(1);

        // Wait for the user input and measure the time
        auto start = chrono::steady_clock::now();
        char input = toupper(_getch()); // Capture user input
        auto end = chrono::steady_clock::now();
        
        // Score based on correctness and reaction time
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

        // Add step score to total minigame score
        minigame3Score += score3;

        // Short pause before next round
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Save mixing satisfaction score to customer object
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
// Preparation station for preparing lemonade ingredients
void preparationStation(Customer& customer) {
    bool canServeCustomer = true;

    // 1. Convert customer preferences to required stock amounts
    // Calculate sugar needed based on sugar level preference
    int sugarNeeded = 0;
    if (customer.sugarLevel == "0%") sugarNeeded = 0;
    else if (customer.sugarLevel == "25%") sugarNeeded = 10;
    else if (customer.sugarLevel == "50%") sugarNeeded = 20;
    else if (customer.sugarLevel == "75%") sugarNeeded = 30;
    else if (customer.sugarLevel == "100%") sugarNeeded = 40;

    // Calculate ice needed based on ice amount preference
    int iceNeeded = 0;
    if (customer.iceAmount == "None") iceNeeded = 0;
    else if (customer.iceAmount == "Less Ice") iceNeeded = 1;
    else if (customer.iceAmount == "Regular") iceNeeded = 2;
    else if (customer.iceAmount == "Extra Ice") iceNeeded = 3;

    // Calculate water needed based on cup size
    int waterNeeded = 0;
    if (customer.cupSize == "Small") waterNeeded = 200;
    else if (customer.cupSize == "Medium") waterNeeded = 350;
    else if (customer.cupSize == "Large") waterNeeded = 500;

    // 2. Check if sufficient stocks are available
    if (currentSaveFile.stocks.lemons < customer.slices) canServeCustomer = false;
    if (currentSaveFile.stocks.water < waterNeeded) canServeCustomer = false;
    if (currentSaveFile.stocks.sugar < sugarNeeded) canServeCustomer = false;
    if (currentSaveFile.stocks.cups < 1) canServeCustomer = false;
    if (currentSaveFile.stocks.ice < iceNeeded) canServeCustomer = false;

    // Handle insufficient stocks scenario
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

    // 3. Update stocks or deduct used ingredients from inventory
    currentSaveFile.stocks.lemons -= customer.slices;
    currentSaveFile.stocks.water -= waterNeeded;
    currentSaveFile.stocks.sugar -= sugarNeeded;
    currentSaveFile.stocks.cups -= 1;
    currentSaveFile.stocks.ice -= iceNeeded;

    // MINIGAME 1: CATCH THE LEMON - Reaction time game
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

    // Process each lemon slice in order
    for (int i = 0; i < customer.slices; i++) {
        char targetKey = 'A' + rand() % 26; // Random letter from A to Z
    
        // Random delay to make timing challenging
        int delaySeconds = 1 + rand() % 2;
        this_thread::sleep_for(chrono::seconds(delaySeconds));
    
        // Show key to press
        centerText("PRESS " + string(1, targetKey) + " NOW!"); space(1);
        auto start = chrono::steady_clock::now();
    
        // Get user input and calculate reaction time
        char input = toupper(_getch());
        auto end = chrono::steady_clock::now();
        double reactionTime = chrono::duration<double>(end - start).count();
    
        // Score based on correctness and speed
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

    // Calculate average score across all lemon slices
    minigame1Score /= customer.slices;

    // Proceed to the next minigame
    goTo(1, 29);
    centerText("Press 'Enter' to continue..."); 
    char key1;
    do {
        key1 = _getch();
    } while (key1 != 13);

    // CLEAR previous minigame display
    goTo(1, 29);
    displayBlockFormat(72, 1, ' ');

    goTo(1, 11);
    displayBlockFormat(72, 18, ' ');
    goTo(1, 11);
    
    // MINIGAME 2: SUGAR RUSH! - Choice matching game
    centerText("-= SUGAR -=- RUSH! =-");
    space(1);
    centerText("Select the customer's preferred sugar level:"); space(2);
    centerText("[1] 0% | [2] 25% | [3] 50% | [4] 75% | [5] 100%"); space(1);

    int score2 = 0;
    int minigame2Score = 0;

    // Define sugar level options
    vector<string> sugarLevels = {"0%", "25%", "50%", "75%", "100%"};

    char input = _getch();  // wait for key press
    int index = input - '1';  // convert char '1'-'5' to index 0-4

    // Score based on how close selection is to correct sugar level
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
    
    // Save preparation satisfaction score (average of both minigames)
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

// Generates a random customer name
string generateRandomName() {
    vector<string> names = {"Alex", "Chris", "Taylor", "Jordan", "Jamie", "Morgan", "Casey", "Riley", "Sam", "Charlie"};
    return names[rand() % names.size()];
}

// Saves customer order details to a file
void saveCustomerData(const Customer& customer) {
    ofstream outFile("orders.txt", ios::app); // Open fila in append mode
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

// Displays customer order notification on screen
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