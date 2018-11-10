#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
using namespace std;

class Board {
	static int target[3][3];	// target board position
	static int xt, yt;

	int board[3][3] = { 0 };	// current board position
	int x, y;					// coordinates of an empty field
public:
	Board() {
		x = y = -1;
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
	}
	Board& operator=(Board&& b) {
		if (&b != this)
			copy(b);
	}

	friend istream& operator>>(istream& is, Board& b);
	friend ostream& operator<<(ostream& os, const Board& b);

	void generate();

	bool isSolved() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (board[i][j] != target[i][j])
					return false;
		return true;
	}
	bool isSolvable();

	static void loadTarget();
	static void generateTarget();
private:
	static int* generateArray();
};

#endif