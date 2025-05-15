#include <iostream>  
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   

using namespace std;

// Constants for game mechanics
const int BAR_WIDTH = 30;      // Total width of the skill check bar
const int SUCCESS_START = 10;  // Start position of the success zone
const int SUCCESS_END = 20;    // End position of the success zone

// Hide the console cursor to make UI cleaner
// Usess Windows API to modify console cursor properties
void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Restore the console cursor visibility
//  Called at the end of the program to reset console state
void showCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Repositions the console cursor to position (0, 2)
// Used to overwrite the same area of the the console for animation
void moveCursor() {
    COORD coord = {0, 2};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Drwas the skill check bar and the moving indicator
void drawBar(int pos) {
    // Top border of the bar
    cout << "+";
    for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
    cout << "+" << endl;

    // Middle section with the success zone marked by vertical bars
    cout << "|";
    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i >= SUCCESS_START && i <= SUCCESS_END) cout << "|"; // Success zone indicator
        else if (i == pos) cout << "o"; // Moving indicator
        else cout << " ";
    }
    cout << "|" << endl;

    // Bottom border of the bar
    cout << "+";
    for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
    cout << "+" << endl;

    // draw the indicator (^) at the current position
    for (int i = 0; i < BAR_WIDTH + 2; i++) cout << " "; // Clear previous indicaotr
    cout << "\r";  // Return to beginning of the line
    for (int i = 0; i < pos + 1; i++) cout << " "; // Position the indicator
    cout << "^" << endl; // draw the indicaotr
}
 
int main() {
    int pos = 0;         // Current position of the indicator
    int direction = 1;   // Direction of movement (1 = right, -1 = left)
    bool running = true; // Game state flag

    hideCursor(); // Hide cursor fo cleaner UI



    cout << "Press [SPACE] to stop the indicator inside the success zone!" << endl; 
	
    moveCursor(); 

    // Main game loop
    while (running) {
        moveCursor();  // Reset cursor position for redrawing

        drawBar(pos);  // Draw the bar and indicator

        // Check for keyboard input
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {  // Space bar pressed
                running = false;  // Stop the game loop
                break;
            }
        }

        // Update the position of the indicator
        pos += direction;
        
        // Reverse direction when hitting edges
        if (pos >= BAR_WIDTH - 1 || pos <= 0) direction *= -1;

        // Difficulty mechanic: move faster inside the success zone
        if (pos >= SUCCESS_START && pos <= SUCCESS_END)
            Sleep(1);  // Faster speed in success zone (1ms delay)
        else
            Sleep(5);  // Normal speed outside success zone (5ms delay)
    }

    // Final redraw to show where the indicstor stopped
    moveCursor();
    drawBar(pos);
    cout << endl;

    // Dsiplay the result based on the final position
    if (pos >= SUCCESS_START && pos <= SUCCESS_END)
        cout << "Result: SUCCESS! You hit the target!" << endl;
    else
        cout << "Result: FAILED! Better luck next time!" << endl;

    cout << "\nPress any key to exit...";
    _getch();

    showCursor();  
    return 0;
}
