#ifndef STATION_H
#define STATION_H

#include <string>
using namespace std;
/*------------------- FUNCTION DECLARATIONS -------------------*/
/*This structure contains all the information about a customer's order,
including their identity, beverage preferences, and satisfaction levels
for different preparation stages. */
struct Customer {
    int customerNumber;            // Unique identifier for the customer
    string name;                   // Customer's name
    string cupSize;                // Size of the cup (e.g., small, medium, large)
    int water;                     // Amount of water needed for the drink
    int slices;                    // Number of lemon slices to add
    string sugarLevel;             // Sugar level preference (e.g., no sugar, half sugar, full sugar)
    string iceAmount;              // Amount of ice requested (e.g., no ice, less ice, regular ice)
    int preparationSatisfaction;   // Customer's satisfaction with the preparation stage (0-100)
    int mixingSatisfaction;        // Customer's satisfaction with the mixing stage (0-100)
    int servingSatisfaction;       // Customer's satisfaction with the serving stage (0-100)
};

// Simulates a skill check with a given difficulty level
int performSkillCheck(int difficulty = 1);

/*------------------- EVALUATION FUNCTIONS -------------------*/

// Generates a summary of the day's performance
// Displays metrics and statistics for the entire day's operation
void daySummary();

// Evaluates the customer's satisfaction with their order
// Calculates and updates the customer satisfaction levels based on service provided
void customerEvaluation(Customer& customer);

/*------------------- STATION FUNCTIONS -------------------*/

// Handles the serving station process for a customer's order
// Manages the final stage of order fulifillment and customer intareaction
void servingStation(Customer& customer);

// Handles the mixing station process for a customer's order
// Manages the mixing of ingredients and preperation of the final lemonade
void mixingStation(Customer& customer);

// Handles the initial preperation of a customer's order
// Manages the inital stage of gathering and preparing ingredients
void preparationStation(Customer& customer);

/*------------------- UTILITY FUNCTIONS -------------------*/

// Generates a random name for customers
// Used when craeting new customer instances without specified names
string generateRandomName();

// Saves customer order data to a file
// Records customer information for analytics and future reference
void saveCustomerData(const Customer& customer);

// Displays a notification for a new order received
// Shows the order details to alert staff about new incoming orders
void displayOrderNotification(const Customer& customer);

#endif // STATION_H