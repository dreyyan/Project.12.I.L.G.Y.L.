/*----------------------- HEADER FILES -----------------------*/
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <queue>

#include "Station.h"
#include "prep.h"
#include "GUI.h"
#include "Utility.h"
using namespace std;
/*-------------------- SCENES DEFINITIONS ---------------------*/
queue<Customer> customerQueue;

// Waits for the user to press Enter to continue
void pressEnterToContinue() {
    goTo(23, 30);
    cout << "Press 'Enter' to Continue...";
    char key;

    // Loop until Enter key is pressed
    while (true) {
        key = _getch();
        if (key == 13) { // If 'Enter' key is pressed
            break;
        }
    }
}

// Displays the welcome screen
void displayText1() {
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#                                                            Welcome!  #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Display a second message indicating good fortune
void displayText2() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#                                            Today is your lucky day!  #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Displays a suspenseful message
void displayText3() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#                                               And for your prize...  #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Reveals the prize which is a lemon
void displayText4() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#                                                   ...a LEMONNN!!!!!  #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Displays a shock or confused reaction of the customer
void displayText5() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#  W-what?...                                                          #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Continues the character's disbelief in receiving a lemon
void displayText6() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#  What am I supposed to do with... a lemon?                           #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Shows a moment of silent pause or contemplation
void displayText7() {
    goTo(1, 26);
cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#  .....                                                               #
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#####################                              #####################)";
}

// Displays ASCII clouds near the top of the screen
void showClouds() {
    goTo(0, 4);
    cout << "     .--.           .--.     .--.           .--.     .--.     " << endl;
}

// Clears the cloud graphics
void hideClouds() {
    goTo(0, 4);
    cout << "                                                              " << endl;
}

// Displays an ASCII art lemonade stand
void showLemonadeStand() {
    goTo(0, 6);
    // Print each line of the lemonade stand using cursor movement
    moveCursor(0, 0, 9, 0); cout << " /******\\"; space(1);
    moveCursor(0, 0, 9, 0); cout << "/########\\"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   [__]"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   |  |"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   |  |"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   |  |"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   |__|"; space(1);
    moveCursor(0, 0, 9, 0); cout << "   [##]"; space(1);
    moveCursor(0, 0, 9, 0); cout << "  /////"; space(1);
    moveCursor(0, 0, 9, 0); cout << " /////|"; space(1);
    moveCursor(0, 0, 9, 0); cout << " |    |"; space(1);
    moveCursor(0, 0, 9, 0); cout << " |    |"; space(1);
    moveCursor(0, 0, 9, 0); cout << " ######"; space(1);
}

// Hides the lemonade stand 
void hideLemonadeStand() {
    goTo(0, 7);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
    moveCursor(0, 0, 8, 0); cout << "          "; space(1);
}

// Displays the player character in ASCII art
void showPlayer() {
    goTo(0, 8);
    // Render the player character line by line
    moveCursor(0, 0, 3, 0); cout << "  .,,,  "; space(1);
    moveCursor(0, 0, 3, 0); cout << "  # 0|"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  #  |"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  .--. "; space(1);
    moveCursor(0, 0, 3, 0); cout << "  /|||"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  ||||"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  ||/|"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  |[]|"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  \\_ /"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  |_||"; space(1);
    moveCursor(0, 0, 3, 0); cout << "  |__]]"; space(1);
}

// Hides the player character from the screen
void hidePlayer() {
    goTo(0, 8);
    moveCursor(0, 0, 3, 0); cout << "        "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "       "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
    moveCursor(0, 0, 3, 0); cout << "       "; space(1);
    moveCursor(0, 0, 3, 0); cout << "     "; space(1);
    moveCursor(0, 0, 3, 0); cout << "      "; space(1);
}

// Shows customer 1 at column 18
void showCustomer1() {
    goTo(0, 8);
    moveCursor(0, 0, 18, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 18, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 18, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 18, 0); cout << "[[__|  "; space(1);
}

// Shows customer 2 at column 25
void showCustomer2() {
    goTo(0, 8);
    moveCursor(0, 0, 25, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 25, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 25, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 25, 0); cout << "[[__|  "; space(1);
}

// Shows customer 3 at column 32
void showCustomer3() {
    goTo(0, 8);
    moveCursor(0, 0, 32, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 32, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 32, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 32, 0); cout << "[[__|  "; space(1);
}

// Show scustomer 4 at column 39
void showCustomer4() {
    goTo(0, 8);
    moveCursor(0, 0, 39, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 39, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 39, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 39, 0); cout << "[[__|  "; space(1);
}

// Shows customer 5 at column 46
void showCustomer5() {
    goTo(0, 8);
    moveCursor(0, 0, 46, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 46, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 46, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 46, 0); cout << "[[__|  "; space(1);
}

// Shows customer 6 at column 53
void showCustomer6() {
    goTo(0, 8);
    moveCursor(0, 0, 53, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 53, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 53, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 53, 0); cout << "[[__|  "; space(1);
}

// Shows customer 7 at column 60
void showCustomer7() {
    goTo(0, 8);
    moveCursor(0, 0, 60, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 60, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 60, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 60, 0); cout << "[[__|  "; space(1);
}

// Shows customer 8 at column 67
void showCustomer8() {
    goTo(0, 8);
    moveCursor(0, 0, 67, 0); cout << ",,,.  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "|0 #  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "|  #  "; space(1);
    moveCursor(0, 0, 67, 0); cout << ".--.  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "|||\\  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "||||  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "|\\||  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "|[]|  "; space(1);
    moveCursor(0, 0, 67, 0); cout << " \\_/  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "||_|  "; space(1);
    moveCursor(0, 0, 67, 0); cout << "[[__|  "; space(1);
}

// Hides customer 1 at column 18
void hideCustomer1() {
    goTo(0, 8);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "      "; space(1);
    moveCursor(0, 0, 18, 0); cout << "       "; space(1);
}

// Hides customer 2 at column 25
void hideCustomer2() {
    goTo(0, 8);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "      "; space(1);
    moveCursor(0, 0, 25, 0); cout << "       "; space(1);
}

// Hides customer 3 at column 32
void hideCustomer3() {
    goTo(0, 8);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "      "; space(1);
    moveCursor(0, 0, 32, 0); cout << "       "; space(1);
}

// Hides customer 4 at column 39
void hideCustomer4() {
    goTo(0, 8);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "      "; space(1);
    moveCursor(0, 0, 39, 0); cout << "       "; space(1);
}

// Hides customer 5 at column 46
void hideCustomer5() {
    goTo(0, 8);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "      "; space(1);
    moveCursor(0, 0, 46, 0); cout << "       "; space(1);
}

// Hides customer 6 at column 53
void hideCustomer6() {
    goTo(0, 8);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "      "; space(1);
    moveCursor(0, 0, 53, 0); cout << "       "; space(1);
}

// Hides customer 7 at column 60
void hideCustomer7() {
    goTo(0, 8);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "      "; space(1);
    moveCursor(0, 0, 60, 0); cout << "       "; space(1);
}

// Hides customer 8 at column 67
void hideCustomer8() {
    goTo(0, 8);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "      "; space(1);
    moveCursor(0, 0, 67, 0); cout << "       "; space(1);
}

// Draws the bottom navigation
void showBottomNavigationMenu() {
    goTo(0, 19);
    displayBlockFormat(57, 1, '#');
    displayVLine(49, 19, 12, '#');
    displayVLine(1, 19, 12, '#');
    displayFormat(57, '#');
}

// Draws the stats panel
void showStatsMenu() {
    displayHLine(57, 19, 16, '#');
    displayVLine(72, 19, 12, '#');
    displayHLine(57, 30, 16, '#');
}

void displayNewGameCutscene() {
    clearScreen(); // Clears the screen before starting the cutscene
    cout << R"(########################################################################
#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#:::::::::::::::::::::::::::::::=#%@@@@#-::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::-@@@@@@@@@::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::@=------#@::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::*========*::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::=-==--==-=::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::::-::::-::::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::::=-::-=::::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::::::-#:-==-:=*::::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::=*#@@*.:*#=.-@@%*+::::::::::::::::::::::::::#
#::::::::::::::::::::::-##%%%@@@#..-*:.-@@@%%%%#+::::::::::::::::::::::#
#::::::::::::::::::::::#%%%%%@@@%..+#-.=@@@%%%%%#-:::::::::::::::::::::#
#::::::::::::::::::::::%%%%%%%@@@.:*#+.*@@%%%%%%%*:::::::::::::::::::::#
#:::::::::::::::::::::*%%%%%%%@@@.-##*:#@@%%%%%%%#:::::::::::::::::::::#
#:::::::::::::::::::::#%%%%%%%%@@:-##*:%@%%%%%%%%%-::::::::::::::::::::#
#::::::::::::::::::::*%%%%%%%%%%@-=###-@@%%%%%%%%%#::::::::::::::::::::#
#:::::::::::::::::::*%%%%###%%%%@+=###=%%%%%%#*%%%%#:::::::::::::::::::#
#::::::::::::::::::#%%%%%+=#%%%%#++###+#%%%%#+=%%%%%#=:::::::::::::::::#
#:::::::::----:-*#%%%%%%#--*%%%%%*+###*#%%%%#=:*%%%%%%%#=-----:::::::::#
#::::::::::------+#%%%%*-::*%%%%#*+###*#%%%%#-::*#%%%%*------::::::::::#
#:::::::::-------=###+:::::+%%%%%**###*#%%%%*:::::=###+-------:::::::::#
#:::::::::--:-:-*#-::::::::+%%%%%+*###*#%%%%*:::::::::*#-:::---::::::::#
#::::::::::::::::::::::::::+%%%%#+*###*#%%%%*::::::::::::::::::::::::::#
#::::::::::::::::::::::::::+%%%%%@%##%@%%%%%*::::::::::::::::::::::::::#)" << endl;
    displayText1(); // Displays the first part of the story text
    pressEnterToContinue(); // wait for user input before proceeding
    displayText2();
    pressEnterToContinue();
    displayText3();
    pressEnterToContinue();
    clearScreen();
    goTo(1, 1);
    // Second ASCII art scene
cout << R"(########################################################################
#:::::::::::::::::::::::::::::::::::::... ......:::::::::::::::::::::::#
#::::::::::::::::::::::.....::::::...  .#%#*++........:::::::::::::::::#
#:::::::::::::::::.......::.......  :%#*=---:.: ..-....::::::::::::::::#
#:::::::::::::..  ...+*#++++...:.=%%%*++++=-+%%*#*++=-..:::::::::::::::#
#::::::::...   #%#**++---=-==+===-:::.*##+*@@-----=---..:::::::::::::::#
#:::::... .-#*+=-====+#*:=----------:-:.+@@=:-=++++++:....:::::::::::::#
#:...  :*#*+=-----+%%#:---------------::..#++++*#%#=+++=...::::::::::::#
#. .*#**==---==+**%@=:-=-------------:---..@@#%@%=-----::..::::::::::::#
#*+====-+=+#++*#@@.:--=------------::::::.-@@#.+--======:.:::::::::::::#
#===-==+=++*+*@#@@.:=----:----------::::::..@.*#*++***#%+..::::::::::::#
#=++==---===+@@@@::--:-------------::::::::.@@@@@%%##**...:::::::::::::#
#-------=====+*@=:-:=:.=---------.=::::::::.@#=:.  *#....::::::::::::::#
#---=--====+++#@.:---::--:-------:--::-:-:.*%=----:. ..::::::::::::::::#
#==--====--=*##%.-=--:------=-=:--:---::-.:@#*++==*-..:::::::::::::::::#
#-====----=+*##@.---.:---=-==---=---::-:..@%#*#*+#+..::::::::::::::::::#
#=======--==*%%@:-=-=+=-=====-=-:-==:--:.@@#%#***=..:::::::::::::::::::#
#=--==-=-==+*%%@*:---===+=--===++----:..@@*%%#*+:..::::::::::::::::::::#
#=====+----==*%%@::--.-===++*=+-=---..:@%#*+==*...:::::::::::::::::::::#
#=--===-====*#%#@@::-=+==++===--+-.::@@%####++...::::::::::::::::::::::#
#-++====-:==+#@%@@.----=++=+*=--:-*@@@%%%#*++...:::::::::::::::::::::::#
#+==========+%@%@@:---=======***+@@#+++%@#+=...::::::::::::::::::::::::#
#=+=====-=-==+%#+@@@@@@@@@@@@%*=-=@#==-:*%= ..:::::::::::::::::::::::::#
#--===-++=+==+#+*%#=-=:+=-=@%#*+==.*@*---+-..::::::::::::::::::::::::::#
# ...  .   :. ....      .   *-:.   :=   .::::::::::::::::::::::::::::::#)" << '\n'; 
    displayText4(); // New screen, new story text
    pressEnterToContinue();
    clearScreen();
    goTo(1, 1);
    // Third ASCII art scene
cout << R"(########################################################################
#::---+======++++*********###*##***##*****#######%########%#%#####%%%%*#
#:::::-:---==++++=+*++**********#########***#######################%%%*#
#:---:---===++++++*+++*********@@@+-%@@@###########################%%%+#
#.::::----=-==+++++++*********@@  @%=  @%##############*#############%+#
#...:::------===+++++++++****#* @@%#@@ *@#*#####################%#%#%%+#
#:-------==++++++++****+*****#@ @#@@@@. @**#####################%####%+#
#::::--==========+++++++++****%#@@%    @%****###################%#####+#
#.:::---=---==+===++++++++******@ @@@@@%**#*##*#######################+#
#::.----=-====++==+++++*+******@@@*********#**###*#############%###%##+#
#.:..::::-:--========+++++**+***@ @*************##################%###+#
#...:.:::----========++++*+*****@@@**********#***#####################+#
#::::-------====-======++++++++***+*************######################+#
#---:--------====+=++++++++++**#@@@@@***********#*################%#%#+#
#-::----==--========+++++++++++#@-@@@@#++*********####################+#
#::.:-------=====+++=+++++++#@@@@@@@@:@@%+=+********###**#############=#
#:::::-----=======+=+++++*#@@@       *@@@@@++****#***#*###############+#
#:-:--------==+===+++++++%@@.           *=@@*+*******#**##############=#
#....::------=====++++*+%@@             .@#@@+*******#################+#
#.:::::-----=====+++****@@+              @@@@%#**#***##**#############+#
#::--------==++=++++***@@@               %@@@@%####****########%%##%##+#
#::::------==+====++**+@@@                @@@@@%#***##*********#####%#+#
#:::--==----==+=++**##%#@*                 #@@@%%########%%%%#####%###+#
#:::--==----==+=++**##%#@*                 #@@@%%########%%%%#####%###+#
#       .........::==++@+                 =*@@%#****+********##********#)" << '\n';
    displayText5();
    pressEnterToContinue();
    clearScreen();
    goTo(1, 1);
cout << R"(########################################################################
#::::::::::::::::::::::::::::. #@@@@@@@@@: .:::::::::::::::::::::::::::#
#::::::::::::::::::::::::::.. %@@@@#**###@%..::::::::::::::::::::::::::#
#::::::::::::::::::::::::::.-#@@@+=---::-%@::::::::::::::::::::::::::::#
#::::::::::::::::::::::::::.#@%+-=#*#*=-:+@.:::::::::::::::::::::::::::#
#::::::::::::::::::::::::::.:++==-*#+=*#=## .::::::::::::::::::::::::::#
#:::::::::::::::::::::::....:*+==--=::#*+=:::::::::::::::::::::::::::::#
#::...........::::::.....=+:..#+==+++-::...::::::::::::::::::::::::::::#
#::-**=--=:::...::::.==****###@%+===-:+*=-...::::::::::::::::::::::::::#
#::...:=*@@@@+:..:::.@%=+=*===*#@@@%%%+-=++-:::::::::::::::::::::::::::#
#:::::..    .%+:..:..=+==*#=--=-:---==--+===.::::::::::::::::::::::::::#
#::::::::::..=#=:....#=-+%%#--##*#*=+==-*+=:..:::::::::::::::::::::::::#
#:::::::::::..*#--.-%+-=@@*#*-:-+*#+-==-=*--:.:::::........::::::::::::#
#::::::::::::.-%#=-++-=+*%**##-=-===+---=%+==:......-++#%-:.:::::::::::#
#::::::::::::..-%#=:-=+..#***#*=-=*=-==--##=-=-=+++*##=.-%*:....:::::::#
#:::::::::::::..:@@#*+..:******+=-++=-===.**==++***+.......%*++::::::::#
#::::::::::::::.. .......******+======--=..=%%#*=....:::::......:::::::#
#:::::::::::::::::..:::.:#***#*+++++===-=:........:::::::::::::::::::::#
#::::::::::::::::::::::.-#******++++=====:.::::::::::::::::::::::::::::#
#:::::::::::::::::::::..-#*****++========-.::::::::::::::::::::::::::::#
#::::::::::::::::::::::.-#******++++=====:.::::::::::::::::::::::::::::#
#:::::::::::::::::::::: -===++===---::... :::::::::::::::::::::::::::::#
#:::::::::::::::::::::: -===++===---::... :::::::::::::::::::::::::::::#
#:::::::::::::::::::::: -===++===---::... :::::::::::::::::::::::::::::#
#::::::::::::::::::::::: ===++===---::.. ::::::::::::::::::::::::::::::#)" << '\n'; 
    displayText6(); // Pre-climax of the story
    pressEnterToContinue();
    clearScreen();
    goTo(1, 1);
    // Fifth ASCII art scene
cout << R"(########################################################################
#=======++========-+*++-::-#@@-::-=+*+============+=======++=====+++===#
#=====++=========-#*==-=@@@@.#@@@=-==+*===========+==========+=====++==#
#====++=========-*+=+==@%.-+.*:.%@+===++==========-::::--======+====++=#
#====+=========-*+=++=*@:-+%:#=*+======+*=====-: .-=*#*=-:  :====+===+=#
#==+=+==========*=+++==@=:=%-%=--==++===*+===- +@@@@@@@@@@@@+.-===+====#
#====++=======-*+=++++==@#-::-=##+-=+++=++==-:@@@@@@@@@@@@@@@@:======+=#
#+====++======-+*=+++++=-=#@-%+:-@+===+=++==:@@@=::=@@@#**%@@@=====+===#
#==============-#=+++=====-#:#==.@#=++==*==--@@.=@*+-:--*+::%@-========#
#======+=======-+#==++*@#.-*:*::+@+=+==*+====@%=++:=++*==++=++:-=======#
#=====++==+=====-+#===-#@@@+.=@@@#-==+*+===+**+++***++#+++++*%%+=======#
#=====+==========-=#*==--+@@=@%+:-==+*+=====--**+++++++++++**======+===#
#=====+============-+#*+=-:*@#:-=+**+=========-#**+++++++***===========#
#=====+=============---=*#*+++***=--=======++==-:+#*****++::-==========#
#======+================---------========++===::++++++++=+=+-:=========#
#=======+++==============================+===-%@@@===++=#@@@@%-:-======#
#==========++++++===============++======++=:=%@@#-+%+==%%####%@@+-=====#
#==========++====+============+===++++++===#@@*=-=%%@%%###%%@@@@++-====#
#=========++======++*+====+++==============+*====%%######*+%.-*+=*#====#
#========+=============++==================+++=*@#########+%::-++*#+===#
#+=====++==============================++==+#*.@##########%@:=#***-==+=#)" << '\n';
    clearScreen();
    goTo(1, 1);
cout << R"(########################################################################
#------------------------:*@#=#=+#=%+=%++#@%++-------------------------#
#---------------------:++%#-@+++**-@=:@===#%:.-------------------------#
#---------------------.@=-@*=@**+=+@=:%+==#@.:-------------------------#
#---------------------.:%*:%#:+++=*#-=#==##+:--------------------------#
#----------------------:.%%=*@+:+++=:*#**##::--------------------------#
#-----------------------:..+@@@@#***#*+@@-.:---------------------------#
#-------------------------.  =+*##%#+=--. .:::...:---------------------#
#-----------------------:.:%*=%*=+*-*%@%#%--=+#@%:---------------------#
#----------------------:.#%=-@%=-*+.:+*+##*:.:..-----------------------#
#---------------------:.%%--%#=.:%*+=.---#*#::-------------------------#
#---------------------.*@#=+*-:=@@@@@@=::=*#+:-------------------------#
#--------------------:.@#+++-:+@@*=-%@@=--+*#.:------------------------#
#--------------------:-@**+----@@@@%+. .--=+#=:------------------------#
#---------::::-------.=@**-==-...+%%@@@---=+@+:------------------------#
#-------:::=-:::....:.=%**:+*=%@@+=-=#@+=-+-%=.---::-------------------#
#-----::-=++#@*-*%%++.=%**:+*=-%@@@@@@#:+-*+%-.:::=-:...:::------------#
#----::+##**:.:=%: +%*=%##+*#=-::#%*#-.=*=#+#+---*=:+@%=+*:....:-------#
#---::**.-=-=+**=+#*==#+-+*#%#==*=:-#*=**#%+#:+%#=+@@.:*+*@@%%*. .:----#
#--:-##%===*#- --*#*+-+=%* :+##==+=*%+*%+-.=.-@*=-. .=:-::  .+@%@@-..:-#
#:.:.-=:++*+==+#*=+***#----=*%@%##%@@*--=%#*@%=:-*@@@=--=%**@*-  :*@%:-#
#:#@::.:+-.-@*.:+++*=..=#=*%#%%@@@*--=+-:*#*.-=+-**  =@%-.-+-*##@@*..=-#
#+ *@*=*#*-@%=::-:-:+++=*#%+-::-+++===+*#- *#%#*+#-%@@#==@@-.*=:=-+*%#-#
#*#+==++++===+==+--+-:-##:.-++*#*+++++++-+++=.+=+#@#++***+#*+#%%%%%%%@-#
#=#=+++++++++++===*%=.@@-:.==:##= .-==---==+*+*=+%+:*++===----::......-#
#:=*=....:::---=*+++*+++=-:===--=++=------:.::==#- ......::::::::------#)" << '\n';
    displayText7(); // Final part of the cutscene narration
    pressEnterToContinue(); // End of cutscene
}

void displayPreGameTransition() {
    // GET DATA
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
        cerr << "Could not open saveFiles.json\n";
        return;
    }

    json data;
    file >> data;

    int day = data[saveFileNum]["player_data"]["day"].get<int>();

    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    space(3); // Add spacing before center text

    // Displays current game day 
    if (day >= 10) {
        centerText(" -= DAY " + to_string(day) + " =- ");
    } else {
        centerText(" -= DAY  " + to_string(day) + " =- ");
    }

    space(4); // Add spacing before bottom border
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayBlockFormat(72, 1, '#'); delayMs(20);
    displayFormat(72, '#'); // Final static border
    delayS(2); // Pause before moving to game area
}

void goToGameArea() {
    bool dayFinished = false;
    int currentHour = 8;

    // 1. Show game area
    goTo(1, 1);
    clearScreen();
    displayBlockFormat(72, 1, '#');
    displayBorder(1, '#');
    displayBlockFormat(72, 1, '#');
    displayBorder(15, '#');
    showStatsMenu(); 
    showBottomNavigationMenu();
    showClouds();
    showLemonadeStand();
    showPlayer();
    displayInformation();

    // OTHERS
    displayTime(currentHour);
    updateMoney();

    srand(time(0));
    // CUSTOMER CHARACTERIZATION
    vector<string> sugarLevels = {"0%", "25%", "50%", "75%", "100%"};
    vector<string> iceAmount = {"None", "Less Ice", "Regular", "Extra Ice"};
    vector<string> cupSizes = {"Small", "Medium", "Large"};
    vector<int> lemonSlices = {1, 2, 3};
    int customerCounter = 1;

    // Wait for 5 seconds before showing the first customer
    delayS(5);

    // Game day loop
    while (!dayFinished) {
        // 1. Generate a customer
        Customer customer;
        string name = generateRandomName();
        customer.customerNumber = customerCounter++;
        customer.name = name;
        customer.cupSize = cupSizes[rand() % cupSizes.size()];
        customer.water = 0;
        // Set water amount based on cup size
        if (customer.cupSize == "Small") customer.water = 200;
        else if (customer.cupSize == "Medium") customer.water = 350;
        else customer.water = 500;
        customer.iceAmount = iceAmount[rand() % iceAmount.size()];
        customer.sugarLevel = sugarLevels[rand() % sugarLevels.size()];
        customer.slices = lemonSlices[rand() % lemonSlices.size()];

        // Add to queue
        customerQueue.push(customer);

        // Limit queue size to 7
        if (customerQueue.size() > 7) {
            customerQueue.pop(); // Remove oldest
        }

        // 2. Save customer order
        saveCustomerData(customer);

        // 3. Show customer graphics based on queue size
        int slot = 1;
        queue<Customer> displayQueue = customerQueue; // Copy so original stays
        map<int, int> customerSlotMap; // Maps customer #
        while (!displayQueue.empty()) {
            Customer c = displayQueue.front();
            displayQueue.pop();

            customerSlotMap[c.customerNumber] = slot;

            switch (slot) {
                case 1: showCustomer1(); break;
                case 2: showCustomer2(); break;
                case 3: showCustomer3(); break;
                case 4: showCustomer4(); break;
                case 5: showCustomer5(); break;
                case 6: showCustomer6(); break;
                case 7: showCustomer7(); break;
            }
            ++slot;
        }

        // 4. Display order notification in the game area
        displayOrderNotification(customer);

        // 5. Wait until 'Enter' key is pressed
        char key1;
        do {
            key1 = _getch();
            if (key1 == 13) {
                // servingStation(customer);
                preparationStation(customer);
            }
        } while (key1 != 13);

        // After order, remove customer queue and hide them
        Customer current = customerQueue.front();
        customerQueue.pop();
        
        // Get the slot number used to show this customer
        int currentSlot = customerSlotMap[current.customerNumber];

        // Hide the customer from the screen
        switch (currentSlot) {
            case 1: hideCustomer1(); break;
            case 2: hideCustomer2(); break;
            case 3: hideCustomer3(); break;
            case 4: hideCustomer4(); break;
            case 5: hideCustomer5(); break;
            case 6: hideCustomer6(); break;
            case 7: hideCustomer7(); break;
        }

        // Refresh UI and info
        goTo(1, 1);
        clearScreen();
    
        displayBlockFormat(72, 1, '#');
        displayBorder(1, '#');
        displayBlockFormat(72, 1, '#');
        displayBorder(15, '#');
    
        // SHOW MENU & GRAPHICS
        showStatsMenu();
        showBottomNavigationMenu();
        showClouds();
        showLemonadeStand();
        showPlayer();
    
        // SHOW INFORMATION
        displayTime(currentHour);
        displayInformation();
        updateMoney();

        // 6. Wait 10 seconds before next customer
        this_thread::sleep_for(chrono::seconds(10));

        // 7. Update time
        updateTime(currentHour);

        // If served 6 customers, finish the day
        if (customerCounter > currentSaveFile.plan.expectedCustomers) {
            dayFinished = true;
        }
    }

    // Prompt user to press 'Enter' to end the day
    goTo(15, 24);
    cout << "It's closing time...";

    goTo(13, 25);
    cout << "Press 'Enter' to end day";
    char key2;
    do {
        key2 = _getch();
        if (key2 == 13) {
            daySummary(); // Shows summary
        }
    } while (key2 != 13);
}

void startGame() {
    // Pre-conditions
    clearScreen();
    goTo(1, 1); // Reset screen positions

    // GET DATA
    ifstream file("saveFiles.json");
    if (!file.is_open()) {
        cerr << "Could not open saveFiles.json\n";
        return;
    }

    json data;
    file >> data;

    // Game Loop
    while (true) {
        // Day Preparation
        displayDayPrepMenu();
    }
}