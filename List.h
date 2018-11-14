#ifndef _LIST_H_
#define _LIST_H_

#include "Board.h"

class List {
	struct Node {
		Board *board;
		Node *next;
		Node(Board *b, Node *nxt = nullptr) {
			board = b;
			next = nxt;
		}
	};
	Node *first;
public:
	List() {
		first = nullptr;
	}
	~List() {
		while (first) {
			Node *old = first;
			first = first->next;
			delete old->board;
			delete old;
		}
	}
	void add(Board *b) {
		Node *node = new Node(b, first);
		first = node;
	}
	bool contains(Board *b) {
		Node *curr = first;
		while (curr) {
			if (*b == *curr->board)
				return true;
			curr = curr->next;
		}
		return false;
	}
	Board* remove(Board *b) {
		Node *curr = first, *prev = nullptr;
		while (curr && *b != *curr->board) {
			prev = curr;
			curr = curr->next;
		}
		if (!curr) return nullptr;
		if (prev) {
			prev->next = curr->next;
		} else {
			first = nullptr;
		}
		Board *board = curr->board;
		delete curr;
		return board;
	}
};


#endif