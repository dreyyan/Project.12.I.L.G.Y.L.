#include <iostream>  
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   

using namespace std;

const int BAR_WIDTH = 30;
const int SUCCESS_START = 10;
const int SUCCESS_END = 20;

// Hide the cursor
void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Show the cursor
void showCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Move the cursor (0,2)
void moveCursor() {
    COORD coord = {0, 2};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBar(int pos) {
    // Top border
    cout << "+";
    for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
    cout << "+" << endl;

    // Success zone bar
    cout << "|";
    for (int i = 0; i < BAR_WIDTH; i++) {
        if (i >= SUCCESS_START && i <= SUCCESS_END) cout << "|";
        else cout << " ";
    }
    cout << "|" << endl;

    // Bottom border
    cout << "+";
    for (int i = 0; i < BAR_WIDTH; i++) cout << "-";
    cout << "+" << endl;

    // Clear arrow line before printing new arrow
    for (int i = 0; i < BAR_WIDTH + 2; i++) cout << " ";
    cout << "\r";  // Return to beginning of the line
    for (int i = 0; i < pos + 1; i++) cout << " ";
    cout << "^" << endl; 
}
 
int main() {
    int pos = 0;
    int direction = 1;
    bool running = true;

    hideCursor(); 



    cout << "Press [SPACE] to stop the indicator inside the success zone!" << endl; 
	
    moveCursor(); 

    while (running) {
        moveCursor(); 

        drawBar(pos);

        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                running = false;
                break;
            }
        }

        pos += direction;
        if (pos >= BAR_WIDTH - 1 || pos <= 0) direction *= -1;

        // Change speed: faster inside success zone
        if (pos >= SUCCESS_START && pos <= SUCCESS_END)
            Sleep(1);  // Faster speed
        else
            Sleep(5);  // Normal speed
    }

    moveCursor();
    drawBar(pos);
    cout << endl;

    if (pos >= SUCCESS_START && pos <= SUCCESS_END)
        cout << "Result: SUCCESS! You hit the target!" << endl;
    else
        cout << "Result: FAILED! Better luck next time!" << endl;

    cout << "\nPress any key to exit...";
    _getch();

    showCursor();  
    return 0;
}
