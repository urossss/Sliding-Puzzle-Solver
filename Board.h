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
	int manhattan;				// heuristic measure
	int level;					// number of moves needed to get to this position from start
	const Board *parrent;		// pointer to previous position

	int inversions;				// number of inversions needed to solve a puzzle, we use this field just to prevent calculating it multiple times
public:
	Board() {
		x = y = inversions = manhattan = -1;
		level = 0;
		prevDir = NONE;
		parrent = nullptr;
	}
	Board(const Board& b) {
		copy(b);
		//parrent = &b;
		//level = b.level + 1;
	}

	Board& operator=(const Board& b) {
		if (&b != this)
			copy(b);
		return *this;
	}

	friend bool operator==(const Board& b1, const Board& b2);
	friend bool operator!=(const Board& b1, const Board& b2);

	friend istream& operator>>(istream& is, Board& b);
	friend ostream& operator<<(ostream& os, const Board& b);

	int h() {	// manhattan value
		return getManhattan();
	}
	int g() {	// steps needed to reach from the start position
		return level;
	}
	int f() {	// total heuristic value
		return g() + h();
	}

	/** 
	 *	Prints the resulting path calculated using Solver::solveAStar()
	 *	and returns number of moves
	 */
	int printPath() const;

	/**
	 *	Direction of the last move that led to this position
	 */
	Direction getPrevDir() {
		return prevDir;
	}

	/**
	 *	Returns a pointer to new board gotten after one move in given direction
	 */
	Board* slide(int d);

	/**
	 *	Generates a random board position
	 */
	void generate();


	/**
	 *	Checks whether a board is in target position
	 */
	bool isSolved() const {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (board[i][j] != target[i][j])
					return false;
		return true;
	}

	/**
	 *	Checks whether it is possible to get to target position from this position
	 */
	bool isSolvable();

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

	/** 
	 *	Number of slides needed to put 0 at same position as in target
	 */
	int slidesNeeded();

	/**
	 *	Copies the whole path from start to solution so that temporary objects can be deleted safely
	 */
	static Board* copySolution(const Board *sol);
	static void deleteSolution(const Board *sol);

	static void loadTarget();
	static void generateTarget();
	static void printTarget();
private:
	void copy(const Board& b);
	Board* slide(Direction d);
	static int* generateArray();
	int inversionsNeeded();
};

#endif