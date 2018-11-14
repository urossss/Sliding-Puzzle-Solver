#include "Board.h"

int Board::target[3][3] = { 0 }, Board::xt = -1, Board::yt = -1;

void Board::loadTarget() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			cin >> target[i][j];
			if (!target[i][j]) {
				xt = i;
				yt = j;
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
	delete[] a;
}

void Board::printTarget() {
	cout << "*****" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			cout << target[i][j] << ' ';
		cout << endl;
	}
	cout << "*****" << endl;
}

int* Board::generateArray() {
	int *a = new int[9], i, j;
	for (int i = 0; i < 9; a[i] = i++);
	for (i = 8; i >= 1; i--) {
		j = (int) (rand() / (RAND_MAX + 1.) * (i + 1));
		swap(a[i], a[j]);
	}
	return a;
}




void Board::copy(const Board &b) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = b.board[i][j];
	x = b.x;
	y = b.y;
	prevDir = b.prevDir;
	parrent = b.parrent;
	level = b.level;
	manhattan = b.manhattan;
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
	delete[] a;
}

int Board::printPath() const {
	int res = -1;
	if (parrent) {
		res = parrent->printPath();
	}
	cout << *this;
	if (!isSolved())
		cout << "  |\n  v\n";
	return res + 1;
}

Board* Board::slide(Direction d) {
	Board *b = new Board(*this);
	b->inversions = -1;
	b->prevDir = NONE;
	b->level = this->level + 1;
	b->parrent = this;
	switch (d) {
	case UP:
		if (b->x == 0) break;
		b->board[b->x][b->y] = b->board[b->x - 1][b->y];
		b->x--;
		b->board[b->x][b->y] = 0;
		b->prevDir = UP;
		break;
	case DOWN:
		if (b->x == 2) break;
		b->board[b->x][b->y] = b->board[b->x + 1][b->y];
		b->x++;
		b->board[b->x][b->y] = 0;
		b->prevDir = DOWN;
		break;
	case LEFT:
		if (b->y == 0) break;
		b->board[b->x][b->y] = b->board[b->x][b->y - 1];
		b->y--;
		b->board[b->x][b->y] = 0;
		b->prevDir = LEFT;
		break;
	case RIGHT:
		if (b->y == 2) break;
		b->board[b->x][b->y] = b->board[b->x][b->y + 1];
		b->y++;
		b->board[b->x][b->y] = 0;
		b->prevDir = RIGHT;
		break;
	default:
		break;
	}
	b->setManhattan();
	return b;
}

Board* Board::slide(int d) {
	return slide((Direction) d);
}

int Board::inversionsNeeded() {			// number of inversions (swaps) needed to get target position
	Board *b = new Board(*this);
	int dx = xt - b->x, dy = yt - b->y;

	while (dx) {
		if (dx > 0)
			b = b->slide(DOWN);
		else
			b = b->slide(UP);
		dx = xt - b->x;
	}
	while (dy) {
		if (dy > 0)
			b = b->slide(RIGHT);
		else
			b = b->slide(LEFT);
		dy = yt - b->y;
	}

	int cnt = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (b->board[i][j] != target[i][j]) {
				for (int ii = 0; ii < 3; ii++)
					for (int jj = 0; jj < 3; jj++)
						if (b->board[ii][jj] == target[i][j]) {
							swap(b->board[i][j], b->board[ii][jj]);
							break;
						}
				cnt++;
			}

	delete b;
	return cnt;
}

void Board::setInversionsNeeded() {
	inversions = inversionsNeeded();
}

void Board::setManhattan() {
	manhattan = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int ii = 0; ii < 3; ii++)
				for (int jj = 0; jj < 3; jj++)
					if (target[ii][jj] == board[i][j]) {
						manhattan += abs(ii - i) + abs(jj - j);
						ii = 3;
						break;
					}
}

int Board::slidesNeeded() {
	Board *b = new Board(*this);
	int dx = xt - b->x, dy = yt - b->y;
	int cnt = 0;

	while (dx) {
		cnt++;
		if (dx > 0)
			b = b->slide(DOWN);
		else
			b = b->slide(UP);
		dx = xt - b->x;
	}
	while (dy) {
		cnt++;
		if (dy > 0)
			b = b->slide(RIGHT);
		else
			b = b->slide(LEFT);
		dy = yt - b->y;
	}
	delete b;
	return cnt;
}

Board* Board::copySolution(const Board* sol) {
	if (sol) {
		Board *cpy = new Board(*sol);
		cpy->parrent = copySolution(cpy->parrent);
		return cpy;
	}
	return nullptr;
}

void Board::deleteSolution(const Board *sol) {
	if (sol) {
		deleteSolution(sol->parrent);
		delete sol;
	}
}

bool Board::isSolvable() {
	if (inversions < 0)
		setInversionsNeeded();
	return !(inversions % 2);
}


bool operator==(const Board & b1, const Board & b2) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (b1.board[i][j] != b2.board[i][j])
				return false;
	return true;
}

bool operator!=(const Board & b1, const Board & b2) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (b1.board[i][j] != b2.board[i][j])
				return true;
	return false;
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
	os << "-----\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			os << b.board[i][j] << ' ';
		}
		os << endl;
	}
	os << "-----\n";
	return os;
}
