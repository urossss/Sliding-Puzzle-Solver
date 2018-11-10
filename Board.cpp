#include "Board.h"

int Board::target[3][3] = { 0 }, Board::xt = -1, Board::yt = -1;

void Board::copy(const Board &b) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = b.board[i][j];
	x = b.x;
	y = b.y;
}

int* Board::generateArray() {
	int a[] = { 0, 1, 2, 3 ,4 ,5 ,6 ,7 ,8 }, i, j;
	for (i = 8; i >= 1; i--) {
		j = rand() / (RAND_MAX + 1.) * (i + 1);
		swap(a[i], a[j]);
	}
	return a;
}

void Board::generate() {
	int *a = generateArray();
	for (int i = 0; i < 9; i++) {
		board[i / 3][i % 3] = a[i];
		if (!a[i]) {
			x = i / 3;
			y = i % 3;
		}
	}
}

bool Board::isSolvable() {
	Board b = *this;
	int dx = xt - b.x, dy = yt - b.y;
	
	return false;
}

void Board::loadTarget() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			cin >> target[i][j];
			if (!target[i][j]) {
				xt = i / 3;
				yt = i % 3;
			}
		}
}

void Board::generateTarget() {
	int *a = generateArray();
	for (int i = 0; i < 9; i++) {
		target[i / 3][i % 3] = a[i];
		if (!a[i]) {
			xt = i / 3;
			yt = i % 3;
		}
	}
}



istream& operator>>(istream& is, Board& b) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			is >> b.board[i][j];
			if (!b.board[i][j]) {
				b.x = i;
				b.y = j;
			}
		}
	return is;
}

ostream& operator<<(ostream& os, const Board& b) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			os << b.board[i][j] << ' ';
		}
		os << endl;
	}
	return os;
}
