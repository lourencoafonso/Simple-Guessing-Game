import random
import time
import os

class Colors:
    RESET = '\033[0m'
    RED = '\033[31m'
    YELLOW = '\033[33m'

def selectDifficulty():
    print("\nSelect Difficulty Level:")
    print("1. Easy (1-10)")
    print("2. Medium (1-50)")
    print("3. Hard (1-100)")
    
    while True:
        choice = input("\nEnter your choice (1/2/3): ").strip()
        if choice == '1':
            return 10
        elif choice == '2':
            return 50
        elif choice == '3':
            return 100
        else:
            print(Colors.RED + "\nInvalid choice. Please select 1, 2, or 3." + Colors.RESET)
            time.sleep(1)

def playGame():
    difficulty = selectDifficulty()
    randomNumber = random.randint(1, difficulty)
    attempts = 0

    print(f"\nI have selected a number between 1 and {difficulty}. Can you guess it?")

    while True:
        guess = input("\nEnter your guess: ").strip()
        attempts += 1
        
        # Validate numeric input
        try:
            guess = int(guess)
        except ValueError:
            print(Colors.YELLOW + "\nPlease enter a valid number." + Colors.RESET)
            time.sleep(1)
            continue
        
        # Check bounds
        if guess < 1 or guess > difficulty:
            print(Colors.RED + f"\nOut of bounds! Please guess between 1 and {difficulty}." + Colors.RESET)
            time.sleep(1)
            continue

        # Guess logic
        if guess < randomNumber:
            print("\nToo low! Try again.")
        elif guess > randomNumber:
            print("\nToo high! Try again.")
        else:
            print(f"\n🎉 Congratulations! You guessed the number {randomNumber} in {attempts} attempts.")
            player_name = input("Enter your name: ").strip() or "Anonymous"

            # Select leaderboard file based on difficulty
            if difficulty == 10:
                leaderboard_file = 'Results_Easy.txt'
            elif difficulty == 50:
                leaderboard_file = 'Results_Medium.txt'
            else:
                leaderboard_file = 'Results_Hard.txt'

            leaderboard = []

            # Load existing leaderboard
            if os.path.exists(leaderboard_file):
                with open(leaderboard_file, 'r') as file:
                    lines = file.readlines()
                    for line in lines[1:]:  # skip "LEADERBOARD:"
                        line = line.strip()
                        if line:
                            name, tries = line.split(',')
                            leaderboard.append((name, int(tries)))

            # Add and sort results
            leaderboard.append((player_name, attempts))
            leaderboard.sort(key=lambda x: x[1])
            leaderboard = leaderboard[:5]

            # Write updated leaderboard
            with open(leaderboard_file, 'w') as file:
                file.write("LEADERBOARD:\n")
                for name, tries in leaderboard:
                    file.write(f"{name},{tries}\n")

            # Display leaderboard
            print("\n🏆 LEADERBOARD:")
            for i, (name, tries) in enumerate(leaderboard, start=1):
                print(f"{i}. {name} - {tries} attempts")

            break  # Exit guessing loop

while True:
    playGame()
    option = input("\nDo you want to play again? (yes/no): ").strip().lower()
    if option == 'no':
        print("\nThank you for playing! Goodbye!")
        break
    elif option != 'yes':
        print(Colors.RED + "\nInvalid input. Please enter 'yes' or 'no'." + Colors.RESET)
