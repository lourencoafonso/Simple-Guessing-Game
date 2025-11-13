#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"

using namespace std;

int selectDifficulty() {
    cout << "\nSelect Difficulty Level:"
        "\n 1. Easy (1-10)"
        "\n 2. Medium (1-50)"
        "\n 3. Hard (1-100)"
        "\n";
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear(); // clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << RED << "\nInvalid input. Please enter a number.\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
        if (choice >= 1 && choice <= 3) {
            return choice;
        } else {
            cout << RED << "\nInvalid Choice. Please try again.\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "Welcome to the Simple Guessing Game!\n";
    int difficulty = selectDifficulty();
    int maxNumber;
    switch (difficulty) {
        case 1: maxNumber = 10; break;
        case 2: maxNumber = 50; break;
        case 3: maxNumber = 100; break;
        default: maxNumber = 10; // Fallback
    }

    int targetNumber = rand() % maxNumber + 1;
    int userGuess = 0;
    int attempts = 0;

    cout << "\nI have selected a number between 1 and " << maxNumber << ". Can you guess it?\n";

    while (userGuess != targetNumber) {
        cout << "Enter your guess: ";
        if (!(cin >> userGuess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Please enter a valid number.\n" << RESET;
            continue;
        }
        attempts++;

        if (userGuess < 1 || userGuess > maxNumber) {
            cout << RED << "Invalid guess. Please enter a number between 1 and " << maxNumber << ".\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }

        if (userGuess < targetNumber) {
            cout << YELLOW << "Too low! Try again.\n" << RESET;
        } else if (userGuess > targetNumber) {
            cout << YELLOW << "Too high! Try again.\n" << RESET;

        } else {
            cout << "\nCongratulations! You've guessed the number " << targetNumber 
                << " in " << attempts << " attempts.\n";
        }
    }

    char playAgain;
    cout << "Play again? (y/n): ";
    cin >> playAgain;
    if (tolower(playAgain) == 'y') main();

    return 0;
}