#include <iostream>
#include <cstdlib>

using namespace std;

int guess () {
	bool correct = false;
	int random;
	int max = 100;
	int min = 0;
	int numGuesses = 1;
	string userInput;
	while (!correct) {
		random = min + (rand() % (max - min + 1));
		cout << "The computer has guessed " << random << endl;
		cout << "Please input if the number is 'high', 'low', or 'correct'." << endl;
		cin >> userInput;
		if (userInput == "high") {
			max = random;
			numGuesses++;
		}
		if (userInput == "low") {
			min = random;
			numGuesses++;
		}
		if (userInput == "correct") {
			correct = true;
		}
	}
	return numGuesses;
}

int main () {
	cout << "Enter a number between 0 - 100 for the computer to guess: ";
	int i;
	cin >> i;
	cout << "You have chosen the number " << i << endl;
	cout << "The computer will now attempt to guess this number" << endl;
	int guesses = guess();
	cout << "The computer has guessed your number in " << guesses << " tries!" << endl;
}