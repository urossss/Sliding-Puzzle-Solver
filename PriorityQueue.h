#ifndef _PQ_H_
#define _PQ_H_

#include "Board.h"

class PriorityQueue {
	struct PQNode {
		Board *board;
		PQNode *next;
		PQNode(Board *b) {
			board = b;
			next = nullptr;
		}
	};
	PQNode *front;
public:
	PriorityQueue() {
		front = nullptr;
	}
	~PriorityQueue() {
		while (front) {
			PQNode *old = front;
			front = front->next;
			delete old;
		}
	}
	bool empty() {
		return front == nullptr;
	}
	void insert(Board *b) {
		PQNode *newElem = new PQNode(b), *curr = front, *prev = nullptr;
		while (curr && b->f() >= curr->board->f()) {
			prev = curr;
			curr = curr->next;
		}
		newElem->next = curr;
		if (!prev) {
			front = newElem;
		} else {
			prev->next = newElem;
		}
	}
	Board* remove() {
		if (front) {
			Board *b = front->board;
			front = front->next;
			return b;
		}
		return nullptr;
	}
	bool contains(Board *b) {
		PQNode *curr = front;
		while (curr) {
			if (*b == *curr->board)
				return true;
			curr = curr->next;
		}
		return false;
	}
	Board* remove(Board *b) {
		PQNode *curr = front, *prev = nullptr;
		while (curr && *b != *curr->board) {
			prev = curr;
			curr = curr->next;
		}
		if (!curr) return nullptr;
		if (prev) {
			prev->next = curr->next;
		} else {
			front = nullptr;
		}
		return curr->board;
	}
};

#endif