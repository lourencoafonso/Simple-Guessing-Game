#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>

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
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "\nInvalid input. Please enter a number.\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
            continue;
        }
        if (choice >= 1 && choice <= 3)
            return choice;
        else {
            cout << RED << "\nInvalid Choice. Please try again.\n" << RESET;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

// Struct to store leaderboard entries
struct Entry {
    string name;
    int attempts;
};

// Read leaderboard file
vector<Entry> readLeaderboard(const string& filename) {
    vector<Entry> leaderboard;
    ifstream file(filename);
    if (!file.is_open()) return leaderboard; // file might not exist yet

    string line;
    getline(file, line); // skip "LEADERBOARD:"
    while (getline(file, line)) {
        if (line.empty()) continue;
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string name = line.substr(0, commaPos);
            int tries = stoi(line.substr(commaPos + 1));
            leaderboard.push_back({name, tries});
        }
    }
    file.close();
    return leaderboard;
}

// Write leaderboard to file
void writeLeaderboard(const string& filename, vector<Entry>& leaderboard) {
    ofstream file(filename, ios::trunc);
    file << "LEADERBOARD:\n";
    for (const auto& entry : leaderboard) {
        file << entry.name << "," << entry.attempts << "\n";
    }
    file.close();
}

// Display leaderboard
void showLeaderboard(const vector<Entry>& leaderboard) {
    cout << "\n🏆 LEADERBOARD:\n";
    int rank = 1;
    for (const auto& entry : leaderboard) {
        cout << rank++ << ". " << entry.name << " - " << entry.attempts << " attempts\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "Welcome to the Simple Guessing Game!\n";

    while (true) {
        int difficulty = selectDifficulty();
        int maxNumber;
        string filename;

        if (difficulty == 1) {
            maxNumber = 10;
            filename = "Results_Easy.txt";
        } else if (difficulty == 2) {
            maxNumber = 50;
            filename = "Results_Medium.txt";
        } else {
            maxNumber = 100;
            filename = "Results_Hard.txt";
        }

        int targetNumber = rand() % maxNumber + 1;
        int userGuess = 0;
        int attempts = 0;

        cout << "\nI have selected a number between 1 and " << maxNumber << ". Can you guess it?\n";

        while (true) {
            cout << "Enter your guess: ";
            if (!(cin >> userGuess)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Please enter a valid number.\n" << RESET;
                continue;
            }

            attempts++;

            if (userGuess < 1 || userGuess > maxNumber) {
                cout << RED << "Invalid guess. Please enter between 1 and " << maxNumber << ".\n" << RESET;
                this_thread::sleep_for(chrono::seconds(1));
                continue;
            }

            if (userGuess < targetNumber) {
                cout << YELLOW << "Too low! Try again.\n" << RESET;
            } else if (userGuess > targetNumber) {
                cout << YELLOW << "Too high! Try again.\n" << RESET;
            } else {
                cout << "\n🎉 Congratulations! You guessed the number " << targetNumber 
                    << " in " << attempts << " attempts.\n";
                break;
            }
        }

        // Record to leaderboard
        cout << "Enter your name: ";
        string playerName;
        cin >> playerName;

        vector<Entry> leaderboard = readLeaderboard(filename);
        leaderboard.push_back({playerName, attempts});

        // Sort ascending by attempts
        sort(leaderboard.begin(), leaderboard.end(), [](const Entry& a, const Entry& b) {
            return a.attempts < b.attempts;
        });

        // Keep top 5
        if (leaderboard.size() > 5)
            leaderboard.resize(5);

        writeLeaderboard(filename, leaderboard);
        showLeaderboard(leaderboard);

        // Ask to play again
        char playAgain;
        cout << "\nPlay again? (y/n): ";
        cin >> playAgain;
        if (tolower(playAgain) != 'y') {
            cout << "\nThanks for playing! Goodbye!\n";
            break;
        }
    }

    return 0;
}
