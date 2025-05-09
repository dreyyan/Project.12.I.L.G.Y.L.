#ifndef STATION_H
#define STATION_H

#include <string>
using namespace std;
/*------------------- FUNCTION DECLARATIONS -------------------*/
struct Customer {
    int customerNumber;
    string name;
    string cupSize;
    int water;
    int slices;
    string sugarLevel;
    string iceAmount;
    int preparationSatisfaction;
    int mixingSatisfaction;
    int servingSatisfaction;
};
// EVALUATION
void daySummary();
void customerEvaluation(Customer& customer);
// STATIONS
void servingStation(Customer& customer);
void mixingStation(Customer& customer);
void preparationStation(Customer& customer);
// OTHERS
string generateRandomName();
void saveCustomerData(const Customer& customer);
// ORDER DISPLAY
void displayOrderNotification(const Customer& customer);
#endif