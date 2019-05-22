#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Ship {
private:
	string name;
	char direction;
	vector<int> row;
	vector<int> col;
	int numHits;
	int size;
public:
	Ship(string shipName, char dir, vector<int> x, vector<int> y, int shipSize) {
		name = shipName;
		direction = dir;
		row = x;
		col = y;
		numHits = 0;
		size = shipSize;
	}

	void hit() {
		numHits++;
	}

	bool isSunk() {
		return numHits == size;
	}

	vector<int> getRow() {
		return row;
	}

	vector<int> getCol() {
		return col;
	}

	int getSize() {
		return size;
	}

	string getName() {
		return name;
	}
};

class Board {
private:
	const static int rows = 10;
	const static int columns = 10;
	vector<Ship> ships;
	int grid[rows][columns];
public:
	void initGrid() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				grid[i][j] = 0;
			}
		}
	}

	void showGrid() {
		cout << "       0      1      2      3      4      5      6      7      8      9   " << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		for (int i = 0; i < rows; i++) {
			cout << i;
			for (int j = 0; j < columns; j++) {
				cout << "  |   " << grid[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	bool hitOrMiss(int x, int y) {
		if (grid[x][y] == 1) {
			return true;
		}
		return false;
	}

	bool occupied(vector<int> row, vector<int> col) {
		for (int i = 0; i < row.size(); i++) {
			if (grid[row[i]][col[i]] == 1) {
				return true;
			}
		}
		return false;
	}

	void placeShip(Ship& s) {
		vector<int> row = s.getRow();
		vector<int> col = s.getCol();
		for (int i = 0; i < row.size(); i++) {
			grid[row[i]][col[i]] = 1;
		}
		ships.push_back(s);
	}

	vector<Ship> *getShips() {
		return &ships;
	}

	void markGuess(int x, int y) {
		grid[x][y] = 1;
	}

	void markHit(int x, int y) {
		grid[x][y] = 9;
	}

	void markMiss(int x, int y) {
		grid[x][y] = 3;
	}

	int getGridLocation(int x, int y) {
		return grid[x][y];
	}
};

int random(int min, int max) {
	return min + rand() % ((max + 1) - min);
}

void setShip(string name, int size, Board& b) {
	while (true) {
		vector<int> r (size);
		vector<int> c (size);
		string direction = "";
		int x;
		int y;
		int *oldx = &x;
		int *oldy = &y;
		cout << "Pick a direction for your Carrier ship (size of " + to_string(size) + ") : Horizontal (H) or Vertical (V)" << endl;
		while (true) {
			cin >> direction;
			if (direction != "Horizontal" && direction != "H" && direction != "h" && direction != "HORIZONTAL"
				&& direction != "Vertical" && direction != "V" && direction != "v" && direction != "VERTICAL") {
				cout << "Entered in direction is not available" << endl;
			} else {
				break;
			}
		}
		if (direction == "Horizontal" || direction == "H" || direction == "h" || direction == "HORIZONTAL") {
			cout << "You have chosen horizontal!" << endl;
		}
		if (direction == "Vertical" || direction == "V" || direction == "v" || direction == "VERTICAL") {
			cout << "You have chosen veritcal!" << endl;
		}
		cout << "Pick a starting x (0-9) coordinate for your ship (size of " + to_string(size) + ")" << endl;
		cin >> x;
		int xval = *oldx;
		cout << "Pick a starting y (0-9) coordinate for your ship (size of " + to_string(size) + ")" << endl;
		cin >> y;
		int yval = *oldy;
		if (direction == "Horizontal" || direction == "H" || direction == "h" || direction == "HORIZONTAL") {
			for (int i = 0; i < size; i++) {
				r.at(i) = x;
				c.at(i) = y++;
			} if (xval > 9 || yval + size > 10) {
				cout << "Ship does not fit on board from entered in coordinates" << endl;
			} else if (b.occupied(r, c) == false) {
				Ship temp(name, 'H', r, c, size);
				b.placeShip(temp);
				break;
			} else {
				cout << "Entered in coordinates are currently occupied by another ship" << endl;
			}
		}
		if (direction == "Vertical" || direction == "V" || direction == "v" || direction == "VERTICAL") {
			for (int i = 0; i < size; i++) {
				c.at(i) = y;
				r.at(i) = x++;
			}
			if (xval + size > 10 || yval > 9) {
				cout << "Ship does not fit on board from entered in coordinates" << endl;
			} else if (b.occupied(r, c) == false) {
				Ship temp(name, 'V', r, c, size);
				b.placeShip(temp);
				break;
			} else {
				cout << "Entered in coordinates are currently occupied by another ship" << endl;
			}
		}
	}
}

void setCShip(string name, int size, Board &b) {
	while (true) {
		srand(time(NULL));
		int dir = random(0, 1);
		int x = random(0, 9);
		int y = random(0, 9);
		int *oldx = &x;
		int *oldy = &y;
		int xval = *oldx;
		int yval = *oldy;
		vector<int> r (size);
		vector<int> c (size);
		if (dir == 0) {
			for (int i = 0; i < size; i++) {
				r.at(i) = x;
				c.at(i) = y++;
			} if (xval <= 9 || yval + size <= 10) {
				if (b.occupied(r, c) == false) {
					Ship temp(name, 'H', r, c, size);
					b.placeShip(temp);
					break;
				}
			}
		}
		if (dir == 1) {
			for (int i = 0; i < size; i++) {
				c.at(i) = y;
				r.at(i) = x++;
			}
			if (xval + size <= 10 || yval <= 9) {
				if (b.occupied(r, c) == false) {
					Ship temp(name, 'V', r, c, size);
					b.placeShip(temp);
					break;
				}
			}
		}
	}
}

void humanTurn(Board &cShips, Board &hGuesses, int &cnumSunk, bool &playing) {
	int hxGuess;
	int hyGuess;
	bool hitOrMiss;
	while (true) {
		cout << "Enter in an x location" << endl;
		cin >> hxGuess;
		cout << "Enter in a y location" << endl;
		cin >> hyGuess;
		if (hGuesses.getGridLocation(hxGuess, hyGuess) == 0) {
			break;
		} else {
			cout << endl << "You have already guessed this location" << endl;
		}
	}
	hitOrMiss = cShips.hitOrMiss(hxGuess, hyGuess);
	if (hitOrMiss) {
		cout << endl << "That was a hit!" << endl << endl;
		hGuesses.markHit(hxGuess, hyGuess);
		cShips.markHit(hxGuess, hyGuess);
		vector<Ship> *ships = cShips.getShips();
		for(int i = 0; i < ships->size(); i++) {
			vector<int> r = ships->at(i).getRow();
			vector<int> c = ships->at(i).getCol();
			for (int j = 0; j < ships->at(i).getSize(); j++) {
				if (r.at(j) == hxGuess && c.at(j) == hyGuess) {
					ships->at(i).hit();
					if (ships->at(i).isSunk()) {
						cout << "You have sunk the computer's " + ships->at(i).getName() + " ship!" << endl;
						cnumSunk++;
						if (cnumSunk == 5) {
							playing = false;
						}
					}
				}
			}
		}
	} else {
		cout << endl << "That was a miss!" << endl << endl;
		hGuesses.markGuess(hxGuess, hyGuess);
		cShips.markMiss(hxGuess, hyGuess);
	}
}

void computerTurn(Board &hShips, Board &cGuesses, int &hnumSunk, bool &playing, string level) {
	int cxGuess;
	int cyGuess;
	bool chitOrMiss;
	while (true) {
		if (level == "Easy") {
			cxGuess = random(0, 9);
			cyGuess = random(0, 9);
			if (cGuesses.getGridLocation(cxGuess, cyGuess) == 0) {
				break;
			}
		}
	}
	chitOrMiss = hShips.hitOrMiss(cxGuess, cyGuess);
	if (chitOrMiss) {
		cGuesses.markHit(cxGuess, cyGuess);
		hShips.markHit(cxGuess, cyGuess);
		vector<Ship> *ships = hShips.getShips();
		for(int i = 0; i < ships->size(); i++) {
			vector<int> r = ships->at(i).getRow();
			vector<int> c = ships->at(i).getCol();
			for (int j = 0; j < ships->at(i).getSize(); j++) {
				if (r.at(j) == cxGuess && c.at(j) == cyGuess) {
					cout << "The computer hit your " + ships->at(i).getName() + " ship at (" + to_string(cxGuess) + ", " + to_string(cyGuess) + ")!" << endl << endl;
					ships->at(i).hit();
					if (ships->at(i).isSunk()) {
						cout << "The computer has sunk your " + ships->at(i).getName() + " ship!" << endl << endl;
						hnumSunk++;
						if (hnumSunk == 5) {
							playing = false;
						}
					}
				}
			}
		}
	} else {
		cout << "The computer missed on its guess of (" + to_string(cxGuess) + ", " + to_string(cyGuess) + ")!" << endl << endl;
		cGuesses.markGuess(cxGuess, cyGuess);
		hShips.markMiss(cxGuess, cyGuess);
	}
}

void gameOver(Board &hShips, Board &cShips, int &hnumSunk, int &cnumSunk) {
	if (cnumSunk == 5) {
		cout << "You have have sunk all the computer's ships and won the game!" << endl;
		cout << endl << "Below is the computer board" << endl << endl;
		cShips.showGrid();
		cout << endl << "Below is your board" << endl << endl;
		hShips.showGrid();
	}
	if (hnumSunk == 5) {
		cout << "The computer sunk all your ships and you have lost the game!" << endl;
		cout << endl << "Below is the computer board" << endl << endl;
		cShips.showGrid();
		cout << endl << "Below is your board" << endl << endl;
		hShips.showGrid();
	}
}

void playEasy(Board &hShips, Board &cShips, Board &hGuesses, Board &cGuesses) {
	cout << "Begin easy game!" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl;
	bool playing = true;
	int hnumSunk = 0;
	int cnumSunk = 0;
	while (playing) {
		humanTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing);
		if (playing == false) {
			break;
		}

		computerTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing, "Easy");
		if (playing == false) {
			break;
		}

		cout << "Below are the guesses you have already made" << endl << endl;
		hGuesses.showGrid();
		cout << endl << "Below is the state of your ships" << endl << endl;
		hShips.showGrid();
	}
	gameOver(hShips, cShips, hnumSunk, cnumSunk);
}

void playMedium(Board &hShips, Board &cShips, Board &hGuesses, Board &cGuesses) {
	cout << "Begin medium game!" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl;
	bool playing = true;
	int hnumSunk = 0;
	int cnumSunk = 0;
	while (playing) {
		humanTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing);
		if (playing == false) {
			break;
		}

		computerTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing, "Medium");
		if (playing == false) {
			break;
		}

		cout << "Below are the guesses you have already made" << endl << endl;
		hGuesses.showGrid();
		cout << endl << "Below is the state of your ships" << endl << endl;
		hShips.showGrid();
	}
	gameOver(hShips, cShips, hnumSunk, cnumSunk);
}

void playHard(Board &hShips, Board &cShips, Board &hGuesses, Board &cGuesses) {
	cout << "Begin hard game!" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl;
	bool playing = true;
	int hnumSunk = 0;
	int cnumSunk = 0;
	while (playing) {
		humanTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing);
		if (playing == false) {
			break;
		}

		computerTurn(hShips, cShips, hGuesses, cGuesses, hnumSunk, playing, "Hard");
		if (playing == false) {
			break;
		}

		cout << "Below are the guesses you have already made" << endl << endl;
		hGuesses.showGrid();
		cout << endl << "Below is the state of your ships" << endl << endl;
		hShips.showGrid();
	}
	gameOver(hShips, cShips, hnumSunk, cnumSunk);
}

int main() {
	cout << "----------------------------------------------------------" << endl;
	cout << "Welcome to the game of Battleship!" << endl;
	cout << "Begin by placing your ships on your board" << endl << endl;

	Board hShips;
	Board cShips;
	Board hGuesses;
	Board cGuesses;

	hGuesses.initGrid();
	cGuesses.initGrid();

	hShips.initGrid();
	hShips.showGrid();
	setShip("Carrier", 5, hShips);
	setShip("Battleship", 4, hShips);
	setShip("Cruiser", 3, hShips);
	setShip("Submarine", 3, hShips);
	setShip("Destroyer", 2, hShips);
	cout << endl << "Below are the ship placements you have made" << endl << endl;
	hShips.showGrid();

	cout << "Setting computer ship placements..." << endl << endl;

	cShips.initGrid();
	setCShip("Carrier", 5, cShips);
	setCShip("Battleship", 4, cShips);
	setCShip("Cruiser", 3, cShips);
	setCShip("Submarine", 3, cShips);
	setCShip("Destroyer", 2, cShips);

	cout << "Computer ships placed!" << endl;

	string level;
	cout << "Select a level of difficulty to play!" << endl;
	cout << "Easy (E), Medium (M) or Hard (H)" << endl;
	while (true) {
		cin >> level;
		if (level == "e" || level == "easy" || level == "E" || level == "EASY") {
			playEasy(hShips, cShips, hGuesses, cGuesses);
			break;
		} else if (level == "m" || level == "medium" || level == "M" || level == "MEDIUM") {
			playMedium(hShips, cShips, hGuesses, cGuesses);
			break;
		} else if (level == "h" || level == "hard" || level == "H" || level == "HARD") {
			playHard(hShips, cShips, hGuesses, cGuesses);
			break;
		} else {
			cout << "Entered in level is not available" << endl;
		}
	}
	return 0;
}