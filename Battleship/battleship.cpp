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
	char grid[rows][columns];
public:
	void initGrid() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				grid[i][j] = ' ';
			}
		}
	}

	void showGrid() {
		cout << "       1      2      3      4      5      6      7      8      9      10   " << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		for (int i = 1; i <= rows; i++) {
			cout << i;
			for (int j = 1; j <= columns; j++) {
				if (i == 10 && j == 1) {
					cout << " |   " << grid[i-1][j-1];
				} else {
					cout << "  |   " << grid[i-1][j-1];
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	bool hitOrMiss(int x, int y) {
		if (grid[x][y] == 'S') {
			return true;
		}
		return false;
	}

	bool occupied(vector<int> row, vector<int> col) {
		for (int i = 0; i < row.size(); i++) {
			if (grid[row[i]][col[i]] == 'S') {
				return true;
			}
		}
		return false;
	}

	void placeShip(Ship& s) {
		vector<int> row = s.getRow();
		vector<int> col = s.getCol();
		for (int i = 0; i < row.size(); i++) {
			grid[row[i]][col[i]] = 'S';
		}
		ships.push_back(s);
	}

	vector<Ship> *getShips() {
		return &ships;
	}

	void markHit(int x, int y) {
		grid[x][y] = 'H';
	}

	void markMiss(int x, int y) {
		grid[x][y] = 'M';
	}

	char getGridLocation(int x, int y) {
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
				cout << "Entered in direction is not horizontal or vertical. Please re-enter the desired direction" << endl;
			} else {
				break;
			}
		}
		if (direction == "Horizontal" || direction == "H" || direction == "h" || direction == "HORIZONTAL") {
			cout << "You have chosen horizontal!" << endl;
		}
		if (direction == "Vertical" || direction == "V" || direction == "v" || direction == "VERTICAL") {
			cout << "You have chosen vertical!" << endl;
		}
		cout << "Pick a starting row (1-10) number for your ship (size of " + to_string(size) + ")" << endl;
		while (true) {
			cin >> x;
			while (cin.fail()) {
				cout << "Please enter in a valid integer number" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> x;
			}
			if (x >= 1 && x <= 10) {
				break;
			} else {
				cout << "Entered in row number is out of range of the board. Please choose a different row number" << endl;
			}
		}
		int xval = *oldx;
		cout << "Pick a starting column (1-10) number for your ship (size of " + to_string(size) + ")" << endl;
		while (true) {
			cin >> y;
			while (cin.fail()) {
				cout << "Please enter in a valid integer number" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> y;
			}
			if (y >= 1 && y <= 10) {
				break;
			} else {
				cout << "Entered in column number is out of range of the board. Please choose a different column number" << endl;
			}
		}
		int yval = *oldy;
		if (direction == "Horizontal" || direction == "H" || direction == "h" || direction == "HORIZONTAL") {
			for (int i = 0; i < size; i++) {
				r.at(i) = x-1;
				c.at(i) = y-1;
				y++;
			} if (xval > 10 || yval + size > 11) {
				cout << "Ship does not fit on board from entered in coordinates. Please choose a different set of coordinates" << endl;
			} else if (b.occupied(r, c) == false) {
				Ship temp(name, 'H', r, c, size);
				b.placeShip(temp);
				break;
			} else {
				cout << "Entered in coordinates are currently occupied by another ship. Please choose a different set of coordinates" << endl;
			}
		}
		if (direction == "Vertical" || direction == "V" || direction == "v" || direction == "VERTICAL") {
			for (int i = 0; i < size; i++) {
				c.at(i) = y-1;
				r.at(i) = x-1;
				x++;
			}
			if (xval + size > 11 || yval > 10) {
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
		int dir = random(0, 1);
		int x = random(1, 10);
		int y = random(1, 10);
		int *oldx = &x;
		int *oldy = &y;
		int xval = *oldx;
		int yval = *oldy;
		vector<int> r (size);
		vector<int> c (size);
		if (dir == 0) {
			for (int i = 0; i < size; i++) {
				r.at(i) = x-1;
				c.at(i) = y-1;
				y++;
			} if (xval <= 10 && yval + size <= 11) {
				if (b.occupied(r, c) == false) {
					Ship temp(name, 'H', r, c, size);
					b.placeShip(temp);
					break;
				}
			}
		}
		if (dir == 1) {
			for (int i = 0; i < size; i++) {
				c.at(i) = y-1;
				r.at(i) = x-1;
				x++;
			}
			if (xval + size <= 11 && yval <= 10) {
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
		cout << "Enter in a row number" << endl;
		while (true) {
			cin >> hxGuess;
			while (cin.fail()) {
				cout << "Please enter in a valid integer number" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> hxGuess;
			}
			if (hxGuess >= 1 && hxGuess <= 10) {
				break;
			} else {
				cout << "Entered in row is out of range" << endl;
			}
		}
		cout << "Enter in a column number" << endl;
		while (true) {
			cin >> hyGuess;
			while (cin.fail()) {
				cout << "Please enter in a valid integer number" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cin >> hyGuess;
			}
			if (hyGuess >= 1 && hyGuess <= 10) {
				break;
			} else {
				cout << "Entered in column is out of range" << endl;
			}
		}
		hxGuess--;
		hyGuess--;
		if (hGuesses.getGridLocation(hxGuess, hyGuess) == ' ') {
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
						cout << "You have sunk the computer's " + ships->at(i).getName() + " ship!" << endl << endl;
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
		hGuesses.markMiss(hxGuess, hyGuess);
		cShips.markMiss(hxGuess, hyGuess);
	}
}

void computerTurn(Board &hShips, Board &cGuesses, int &hnumSunk, bool &playing, string level, bool *prevHit, int *prevx, int *prevy) {
	int cxGuess;
	int cyGuess;
	bool chitOrMiss;
	if (level == "Easy") {
		while (true) {
			int probability = random(0, 9);
			if (probability >= 7) {
				vector<Ship> *ships = hShips.getShips();
				for (int i = 0; i < ships->size(); i++) {
					vector<int> r = ships->at(i).getRow();
					vector<int> c = ships->at(i).getCol();
					for (int j = 0; j < ships->at(i).getSize(); j++) {
						if (cGuesses.getGridLocation(r.at(j), c.at(j)) == ' ') {
							cxGuess = r.at(j);
							cyGuess = c.at(j);
							break;
						}
					}
				}
			} else {
				cxGuess = random(0, 9);
				cyGuess = random(0, 9);
				if (cGuesses.getGridLocation(cxGuess, cyGuess) == ' ') {
					break;
				}
			}
		}
	}
	if (level == "Medium") {
		bool selected = true;
		while (selected) {
			int probHitNextPos = random(0, 9);
			if (probHitNextPos >= 7) {
				if (*prevHit) {
					cxGuess = *prevx;
					cyGuess = *prevy;
					vector<Ship> *ships = hShips.getShips();
					for(int i = 0; i < ships->size(); i++) {
						vector<int> r = ships->at(i).getRow();
						vector<int> c = ships->at(i).getCol();
						for (int j = 0; j < ships->at(i).getSize(); j++) {
							if (r.at(j) == *prevx && c.at(j) == *prevy) {
								if ((j+1 < ships->at(i).getSize()) && (hShips.getGridLocation(r.at(j+1), c.at(j+1)) != 'H'
									&& hShips.getGridLocation(r.at(j+1), c.at(j+1)) != 'M')) {
									cxGuess = r.at(j+1);
									cyGuess = c.at(j+1);
									selected = false;
									break;
								} else if (j == ships->at(i).getSize() - 1 && hShips.getGridLocation(r.at(j), c.at(j)) == 'H') {
									cxGuess = r.at(0);
									cyGuess = c.at(0);
									selected = false;
									break;
								} else if ((j == ships->at(i).getSize()) - 1 && (hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'H'
									&& hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'M')) {
									cxGuess = r.at(j-1);
									cyGuess = c.at(j-1);
									selected = false;
									break;
								} else if (j-1 >= 0) {
									while (hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'S' && (j > 0) && (cxGuess != 0 && cyGuess != 0)) {
										cxGuess = r.at(j-1);
										cyGuess = c.at(j-1);
										j -= 1;
										cout << cxGuess << endl;
										cout << cyGuess << endl;
									}
									selected = false;
									break;
								}
							}
						}
					}
				} 
			} else {
				int probability = random(0, 9);
				if (probability == 9) {
					vector<Ship> *ships = hShips.getShips();
					for (int i = 0; i < ships->size(); i++) {
						vector<int> r = ships->at(i).getRow();
						vector<int> c = ships->at(i).getCol();
						for (int j = 0; j < ships->at(i).getSize(); j++) {
							if (cGuesses.getGridLocation(r.at(j), c.at(j)) == ' ') {
								cxGuess = r.at(j);
								cyGuess = c.at(j);
								break;
							}
						}
					}
				} else {
					cxGuess = random(0, 9);
					cyGuess = random(0, 9);
					if (cGuesses.getGridLocation(cxGuess, cyGuess) == ' ') {
						break;
					}
				}
			}
			if (selected == false) {
				break;
			}
		}
	}
	if (level == "Hard") {
		bool selected = true;
		while (selected) {
			int probHitNextPos = random(0, 9);
			if (probHitNextPos >= 4) {
				if (*prevHit) {
					cxGuess = *prevx;
					cyGuess = *prevy;
					vector<Ship> *ships = hShips.getShips();
					for(int i = 0; i < ships->size(); i++) {
						vector<int> r = ships->at(i).getRow();
						vector<int> c = ships->at(i).getCol();
						for (int j = 0; j < ships->at(i).getSize(); j++) {
							if (r.at(j) == *prevx && c.at(j) == *prevy) {
								if ((j+1 < ships->at(i).getSize()) && (hShips.getGridLocation(r.at(j+1), c.at(j+1)) != 'H'
									&& hShips.getGridLocation(r.at(j+1), c.at(j+1)) != 'M')) {
									cxGuess = r.at(j+1);
									cyGuess = c.at(j+1);
									selected = false;
									break;
								} else if (j == ships->at(i).getSize() - 1 && hShips.getGridLocation(r.at(j), c.at(j)) == 'H') {
									cxGuess = r.at(0);
									cyGuess = c.at(0);
									selected = false;
									break;
								} else if ((j == ships->at(i).getSize()) - 1 && (hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'H'
									&& hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'M')) {
									cxGuess = r.at(j-1);
									cyGuess = c.at(j-1);
									selected = false;
									break;
								} else if (j-1 >= 0) {
									while (hShips.getGridLocation(r.at(j-1), c.at(j-1)) != 'S' && (j > 0) && (cxGuess != 0 && cyGuess != 0)) {
										cxGuess = r.at(j-1);
										cyGuess = c.at(j-1);
										j -= 1;
										cout << cxGuess << endl;
										cout << cyGuess << endl;
									}
									selected = false;
									break;
								}
							}
						}
					}
				} 
			} else {
				int probability = random(0, 9);
				if (probability >= 7) {
					vector<Ship> *ships = hShips.getShips();
					for (int i = 0; i < ships->size(); i++) {
						vector<int> r = ships->at(i).getRow();
						vector<int> c = ships->at(i).getCol();
						for (int j = 0; j < ships->at(i).getSize(); j++) {
							if (cGuesses.getGridLocation(r.at(j), c.at(j)) == ' ') {
								cxGuess = r.at(j);
								cyGuess = c.at(j);
								break;
							}
						}
					}
				} else {
					cxGuess = random(0, 9);
					cyGuess = random(0, 9);
					if (cGuesses.getGridLocation(cxGuess, cyGuess) == ' ') {
						break;
					}
				}
			}
			if (selected == false) {
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
					cout << "The computer hit your " + ships->at(i).getName() + " ship at (" + to_string(cxGuess+1) + ", " + to_string(cyGuess+1) + ")!" << endl << endl;
					ships->at(i).hit();
					(*prevHit) = true;
					if (ships->at(i).isSunk()) {
						cout << "The computer has sunk your " + ships->at(i).getName() + " ship!" << endl << endl;
						hnumSunk++;
						(*prevHit) = false;
						if (hnumSunk == 5) {
							playing = false;
						}
					}
				}
			}
		}
		(*prevx) = cxGuess;
		(*prevy) = cyGuess;
	} else {
		cout << "The computer missed on its guess of (" + to_string(cxGuess+1) + ", " + to_string(cyGuess+1) + ")!" << endl << endl;
		cGuesses.markMiss(cxGuess, cyGuess);
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

void playGame(Board &hShips, Board &cShips, Board &hGuesses, Board &cGuesses, string level) {
	cout << endl << "You have selected " + level + "!" << endl; 
	cout << "Begin game!" << endl;
	cout << "-------------------------------------------------------------------" << endl << endl;
	bool playing = true;
	int hnumSunk = 0;
	int cnumSunk = 0;
	bool prevHit = false;
	int prevx = 0;
	int prevy = 0;
	while (playing) {
		humanTurn(cShips, hGuesses, cnumSunk, playing);
		if (playing == false) {
			break;
		}

		computerTurn(hShips, cGuesses, hnumSunk, playing, level, &prevHit, &prevx, &prevy);
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
	hShips.showGrid();
	setShip("Battleship", 4, hShips);
	hShips.showGrid();
	setShip("Cruiser", 3, hShips);
	hShips.showGrid();
	setShip("Submarine", 3, hShips);
	hShips.showGrid();
	setShip("Destroyer", 2, hShips);
	cout << endl << "Below are the ship placements you have made" << endl << endl;
	hShips.showGrid();

	cout << "Setting computer ship placements..." << endl << endl;

	cShips.initGrid();
	srand(time(NULL));
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
			playGame(hShips, cShips, hGuesses, cGuesses, "Easy");
			break;
		} else if (level == "m" || level == "medium" || level == "M" || level == "MEDIUM") {
			playGame(hShips, cShips, hGuesses, cGuesses, "Medium");
			break;
		} else if (level == "h" || level == "hard" || level == "H" || level == "HARD") {
			playGame(hShips, cShips, hGuesses, cGuesses, "Hard");
			break;
		} else {
			cout << "Entered in level is not available" << endl;
		}
	}
	return 0;
}