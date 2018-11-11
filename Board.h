#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
using namespace std;

class Board {
	static int target[3][3];	// target board position
	static int xt, yt;

	enum Direction { NONE, UP, DOWN, LEFT, RIGHT };

	int board[3][3] = { 0 };	// current board position
	int x, y;					// coordinates of an empty field
	Direction prevDir;			// last move used to get to this position
	int inversions;				// number of inversions needed to solve a puzzle
	int manhattan;				// heuristics...
public:
	Board() {
		x = y = inversions = manhattan = -1;
		prevDir = NONE;
	}
	Board(const Board& b) {
		copy(b);
	}
	Board(Board&& b) {
		copy(b);
	}

	void copy(const Board& b);

	Board& operator=(const Board& b) {
		if (&b != this)
			copy(b);
		return *this;
	}
	Board& operator=(Board&& b) {
		if (&b != this)
			copy(b);
		return *this;
	}

	friend bool operator==(const Board& b1, const Board& b2);

	friend istream& operator>>(istream& is, Board& b);
	friend ostream& operator<<(ostream& os, const Board& b);

	Direction getPrevDir() {
		return prevDir;
	}

	Board* slide(Direction d);
	Board* slide(int d);

	void generate();

	bool isSolved() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (board[i][j] != target[i][j])
					return false;
		return true;
	}
	bool isSolvable();

	int hits();

	int inversionsNeeded();
	int getInversionsNeeded() {
		if (inversions < 0)
			setInversionsNeeded();
		return inversions;
	}
	void setInversionsNeeded();

	int getManhattan() {
		if (manhattan < 0)
			setManhattan();
		return manhattan;
	}
	void setManhattan();

	int slidesNeeded();

	static void loadTarget();
	static void generateTarget();
	static void printTarget();
private:
	static int* generateArray();
};

#endif