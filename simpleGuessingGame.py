import random
import time

class Colors :
    RESET = '\033[0m'     # Resets text color to default
    RED = '\033[31m'      # Red text (used for errors)
    YELLOW = '\033[33m'   # Yellow text (used for warnings)

def selectDifficulty():
    print("\nSelect Difficulty Level:")
    print("1. Easy (1-10)")
    print("2. Medium (1-50)")
    print("3. Hard (1-100)")
    
    while True:
        choice = input("\nEnter your choice (1/2/3): ")
        if choice == '1':
            return 10
        elif choice == '2':
            return 50
        elif choice == '3':
            return 100
        else:
            print(Colors.RED + "\nInvalid choice. Please select 1, 2, or 3." + Colors.RESET)
            time.sleep(1)

difficulty = selectDifficulty()

randomNumber = random.randint(1, difficulty)
attempts = 0

print(f"\nI have selected a number between 1 and {difficulty}. Can you guess it?")

while True:
    guess = input("\nEnter your guess: ")
    attempts += 1
    
    try:
        guess = int(guess)
    except ValueError:
        print(Colors.YELLOW + "\nPlease enter a valid number." + Colors.RESET)
        time.sleep(1)
        continue
    
    if guess < 1 or guess > difficulty:
        print(Colors.RED + f"\nYour guess is out of bounds! Please guess a number between 1 and {difficulty}." + Colors.RESET)
        time.sleep(1)
        continue
    
    if guess < randomNumber:
        print("\nToo low! Try again.")
        continue
    elif guess > randomNumber:
        print("\nToo high! Try again.")
        continue
    else:
        print(f"\nCongratulations! You've guessed the number {randomNumber} in {attempts} attempts.")
    
    while True:
        option = input("\nDo you want to play again? (yes/no): ").strip().lower()
        if option == 'yes':
            difficulty = selectDifficulty()
            randomNumber = random.randint(1, difficulty)
            attempts = 0
            print(f"\nI have selected a new number between 1 and {difficulty}. Can you guess it?")
            break
        elif option == 'no':
            print("\nThank you for playing! Goodbye!")
            exit()
        else:
            print(Colors.RED + "\nInvalid input. Please enter 'yes' or 'no'." + Colors.RESET)
            time.sleep(1)
            continue