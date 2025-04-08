/*----------------------- HEADER FILES -----------------------*/
#pragma once
/*---------------------- GUI PROTOTYPES ----------------------*/
class GUI {

public:
    // Default Constructor
    GUI();
    // Parameterized Constructor
    
/*-------------------------- METHODS -------------------------*/
    // Displays the title header of the game
    void displayTitleHeader() const;
    // Displays the ASCII text for 'Continue'
    void displayContinueText() const;
    // Displays the ASCII text for 'Start'
    void displayStartText() const;
    // Displays the ASCII text for 'Exit'
    void displayExitText() const;
    // Displays a menu interface at the start of the program
    void displayMenu();

    void displayContinueMenu();
    void displayStartMenu();
};