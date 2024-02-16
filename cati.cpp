#include <iostream>
#include <conio.h> // for _getch function
#include <windows.h> // for Sleep function
#include <stdlib.h> // for rand function
#include <vector> // for std::vector
#include <thread> // for std::thread

// Function to set cursor position in console
void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const std::string ASCII_REVERSE = "\x1b[7m";
const std::string ASCII_RESET = "\x1b[0m";
const std::string ASCII_BOLD = "\x1b[1m";
const std::string ASCII_UNDERLINE = "\x1b[4m";
const std::string ASCII_BLINK = "\x1b[5m"; // Blinking text
// Define colors (optional)
const std::string ASCII_BLACK = "\x1b[30m";
const std::string ASCII_RED = "\x1b[31m";
const std::string ASCII_GREEN = "\x1b[32m";
const std::string ASCII_YELLOW = "\x1b[33m";
const std::string ASCII_BLUE = "\x1b[34m";
const std::string ASCII_MAGENTA = "\x1b[35m";
const std::string ASCII_CYAN = "\x1b[36m";
const std::string ASCII_WHITE = "\x1b[37m";
// Background colors (optional)
const std::string ASCII_BG_BLACK = "\x1b[40m";
const std::string ASCII_BG_RED = "\x1b[41m";
const std::string ASCII_BG_GREEN = "\x1b[42m";
const std::string ASCII_BG_YELLOW = "\x1b[43m";
const std::string ASCII_BG_BLUE = "\x1b[44m";
const std::string ASCII_BG_MAGENTA = "\x1b[45m";
const std::string ASCII_BG_CYAN = "\x1b[46m";
const std::string ASCII_BG_WHITE = "\x1b[47m";

// Function to clear screen
void clearScreen() {
    system("cls");
}

// Function to check if two objects collide
bool isColliding(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
    return (x1 < x2 + width2 &&
        x1 + width1 > x2 &&
        y1 < y2 + height2 &&
        y1 + height1 > y2);
}

// Function to play a note of given frequency and duration asynchronously with a 1 millisecond gap
void playNote(int frequency, int duration) {
    // Use std::thread to run Beep() in a separate thread
    std::thread soundThread([=]() {
        Beep(frequency, duration);
    });

    // Detach the thread to allow it to run independently
    soundThread.detach();

    // Add a 1 millisecond delay before returning
    std::this_thread::sleep_for(std::chrono::milliseconds(duration + 1));
}

// Function to set console background color
void setBackgroundColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15); // Reset color
}

int main() {
    // Initial cat position
    int catX = 0;
    int catY = 0;

    // Cat frames
    const char* cat[] = {
        "  /\\_/\\",
        " ( o.o )",
        "  > ^ <",
    };

    // Number of rows in the cat
    int numRows = sizeof(cat) / sizeof(cat[0]);

    // Initial fruit position
    int fruitX = rand() % 60; // Random position within visible range
    int fruitY = rand() % 20; // Random position within visible range

    // Fruit
    const char* fruit = "\u25CF"; // Black circle symbol

    // Score and lives
    int score = 0;
    float lives = 3.0f; // Initial lives with .5 for testing

    // Vector to store arrows
    std::vector<std::pair<int, int>> arrows;
    std::vector<std::pair<int, int>> hearts;

    clearScreen();
    // Draw white square with black borders
     int squareWidth = 44;
     int squareHeight = 10;
     int squareX = (80 - squareWidth) / 2;
     int squareY = (25 - squareHeight) / 2;
    for (int y = squareY; y < squareY + squareHeight; ++y) {
        gotoxy(squareX, y);
        if (y == squareY || y == squareY + squareHeight - 1) {
            for (int x = 0; x < squareWidth; ++x) {
                
            }
        } else {
            gotoxy(squareX, y);
            std::cout << ASCII_BG_WHITE << ASCII_REVERSE << " " << ASCII_RESET;
            gotoxy(squareX + squareWidth - 1, y);
            std::cout << ASCII_BG_WHITE << ASCII_REVERSE << " " << ASCII_RESET;
        }
    }

    // Print "Game Over" in the middle of the square
    gotoxy(squareX + (squareWidth - 9) / 2, squareY + squareHeight / 2 - 3);
    std::cout << ASCII_WHITE << ASCII_BOLD << ASCII_UNDERLINE << ASCII_BLINK << " Controls " << ASCII_RESET;

    // Print "Press any key to exit" at the bottom
    gotoxy(30, squareY + squareHeight / 2 - 2);
    std::cout << "W -> up A -> left"; // Print "Press any key to exit" at the bottom
    gotoxy(30, squareY + squareHeight / 2 - 1);
    std::cout << "S -> down D -> right";
     // Print "Press any key to exit" at the bottom
    gotoxy(30, squareY + squareHeight / 2);
    std::cout << "Spacebar -> Teleport Q -> exit";
    gotoxy(30, squareY + squareHeight / 2 + 1);
    std::cout << "P -> Pause";
    gotoxy(30, squareY + squareHeight / 2 + 2);
    std::cout << "Press any key to play";

    // Wait for a key press to exit
    _getch();

    // Clear screen after exiting
    clearScreen();

    clearScreen();
    bool paused = false;

    // Game loop
    while (lives > 0) {
        if (!paused) {
            clearScreen();

            // Display score
            std::cout << ASCII_BOLD << "Score: " << ASCII_RESET << score << std::endl;

            // Display lives
            gotoxy(80, 0);
            std::cout << "Lives: ";
            int numHearts = std::min(13, static_cast<int>(lives)); // Limit hearts to 13
            for (int i = 0; i < numHearts; ++i) {
                if (i == numHearts - 1 && lives - static_cast<int>(lives) == 0.5) {
                    std::cout << ASCII_BLINK; // Make the last heart blink if lives end with .5
                }
                std::cout << ASCII_RED << (char)3 << ASCII_RESET; // Heart symbol
            }

            // Display cat
            setBackgroundColor();
            for (int i = 0; i < numRows; ++i) {
                gotoxy(catX, catY + i);
                std::cout << cat[i];
            }


            // Display fruit
            gotoxy(fruitX, fruitY);
            std::cout << ASCII_GREEN << (char)5;
            setBackgroundColor();

            // Display arrows
            if (score < 20 && rand() % 5 == 0) { // Decreased arrow frequency
                arrows.push_back({ 70, rand() % 20 });
            }
            for (int i = 0; i < arrows.size(); ++i) {
                gotoxy(arrows[i].first, arrows[i].second);
                std::cout << (char)17; // Arrow symbol
                arrows[i].first--; // Move arrow to the left
                if (isColliding(catX, catY, 7, numRows, arrows[i].first, arrows[i].second, 1, 1)) {
                    lives -= 1.0f; // Decrease lives if arrow hits the cat
                    arrows.erase(arrows.begin() + i); // Remove arrow
                }
                if (arrows[i].first <= 0) {
                    arrows.erase(arrows.begin() + i); // Remove arrow if it goes out of bounds
                }
            }

            // Display hearts
            if (score < 20 && rand() % 25 == 0) { // Decreased heart frequency
                hearts.push_back({ 70, rand() % 20 });
            }
            for (int i = 0; i < hearts.size(); ++i) {
                gotoxy(hearts[i].first, hearts[i].second);
                std::cout << ASCII_RED << (char)3 << ASCII_RESET; // Heart symbol
                hearts[i].first--; // Move heart to the left
                if (isColliding(catX, catY, 7, numRows, hearts[i].first, hearts[i].second, 1, 1)) {
                    lives += 1.5f; // Increase lives if heart is collected by the cat
                    hearts.erase(hearts.begin() + i); // Remove heart
                }
                if (hearts[i].first <= 0) {
                    hearts.erase(hearts.begin() + i); // Remove heart if it goes out of bounds
                }
            }

            // Check collision with fruit
            if (isColliding(catX, catY, 7, numRows, fruitX, fruitY, 1, 1)) {
                score++; // Increase score if cat eats a fruit
                lives += 0.5f; // Increase lives if cat eats a fruit
                fruitX = rand() % 53; // Move fruit to a new random position
                fruitY = rand() % 17;
            }


            // Control boss and cat interaction
            if (_kbhit()) {
                char key = _getch();
                if (key == 'w') {
                    if (catY > 0) catY--;
                } else if (key == 's') {
                    if (catY < 20 - numRows) catY++;
                } else if (key == 'a') {
                    if (catX > 0) catX--;
                } else if (key == 'd') {
                    if (catX < 60 - 7) catX++;
                } else if (key == ' ') {
                    // Teleport cat to a random position
                    catX = rand() % 60;
                    catY = rand() % (20 - numRows);
                    lives -= 0.25f; // Decrease lives by 0.25 when teleporting
                } else if (key == 'q') {
                    exit(0);
                } else if (key == 'p') {
                    paused = true;
                }
            }

           

            // Wait a short time before next frame
            Sleep(100);
        } else {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'P') {
                    paused = false;
                }
            }
            Sleep(100);
        }
    }

    // Game over screen
    clearScreen();

    // Draw white square with black borders
     squareWidth = 44;
     squareHeight = 10;
     squareX = (80 - squareWidth) / 2;
     squareY = (25 - squareHeight) / 2;
    for (int y = squareY; y < squareY + squareHeight; ++y) {
        gotoxy(squareX, y);
        if (y == squareY || y == squareY + squareHeight - 1) {
            for (int x = 0; x < squareWidth; ++x) {
            }
        } else {
            gotoxy(squareX, y);
            std::cout << ASCII_BG_WHITE << ASCII_REVERSE << " " << ASCII_RESET;
            gotoxy(squareX + squareWidth - 1, y);
            std::cout << ASCII_BG_WHITE << ASCII_REVERSE << " " << ASCII_RESET;
        }
    }

    // Print "Game Over" in the middle of the square
    gotoxy(squareX + (squareWidth - 9) / 2, squareY + squareHeight / 2);
    std::cout << ASCII_WHITE << ASCII_BOLD << ASCII_UNDERLINE << ASCII_BLINK << " Game Over " << ASCII_RESET;

    // Print "Press any key to exit" at the bottom
    gotoxy(30, squareY + squareHeight + 1);
    std::cout << "Press any key to exit";

    // Wait for a key press to exit
    _getch();

    // Clear screen after exiting
    clearScreen();

    return 0;
}
