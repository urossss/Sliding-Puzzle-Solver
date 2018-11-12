#include "Tree.h"


Tree& Tree::add(Board *b) {
	Node *node;
	if (!root) {
		node = root;
	} else {
		node = nodeWithLessThenMChildren(root, m);
	}
	return add(b, node);
}

Tree& Tree::add(Board *b, Node *prev) {
	Node *tmp = new Node(b);
	if (!prev) {
		root = tmp;
		bestSoFar = root;
	} else {
		if (!prev->firstChild) {
			prev->firstChild = tmp;
		} else {
			Node *child = prev->firstChild;
			while (child->sibling) {
				child = child->sibling;
			}
			child->sibling = tmp;
		}
	}
	n++;
	return *this;
}

void Tree::printSolution() {
	cout << "\nSolution:" << endl;
	Node *tmp = root;
	while (tmp) {
		if (tmp->firstChild) {
			cout << *tmp->board;
			cout << "  |\n  v\n";
			tmp = tmp->firstChild;
		} else {
			if (tmp->board->isSolved()) {
				cout << *tmp->board;
				return;
			}
			tmp = tmp->sibling;
		}
	}
}

void Tree::deleteTree(Node *root) {	// deleting all nodes in a tree
	if (root) {
		deleteTree(root->firstChild);
		deleteTree(root->sibling);
		delete root;
		root = nullptr;
	}
}

int Tree::numberOfChildren(Node *root) {	// returns number of children for a single node
	if (!root) return 0;
	int cnt = 0;
	Node *child = root->firstChild;
	while (child) {
		child = child->sibling;
		cnt++;
	}
	return cnt;
}

Tree::Node* Tree::nodeWithLessThenMChildren(Node *root, int m) {	// returns first node with less then m children so that a tree will always be (almost) complete
	Queue q;
	q.insert(root);
	while (!q.empty()) {
		Node *next = (Node*) q.remove();
		int cnt = 0;
		Node *child = next->firstChild;
		while (child) {
			q.insert(child);
			child = child->sibling;
			cnt++;
		}
		if (cnt < m)
			return next;
	}
	return nullptr;
}

void Tree::printChildren(Node *root) {	// prints all root's children
	if (root) {
		Node *child = root->firstChild;
		while (child) {
			cout << *child->board << "*****" << endl;
			child = child->sibling;
		}
		cout << endl;
	}
}

void Tree::preorderPrint(Node *root) {	// prints all nodes in preorder, one node (with its children) per line
	if (root) {
		cout << *root->board;
		//printChildren(root);

		preorderPrint(root->firstChild);
		preorderPrint(root->sibling);
	}
}

void Tree::nodesAtLevel(Node *root, int *cnt, int level) {
	if (root) {
		cnt[level]++;
		nodesAtLevel(root->firstChild, cnt, level + 1);
		nodesAtLevel(root->sibling, cnt, level);
	}
}

int Tree::numberOfNodesWithDegreeM(Node* root, int m) {
	return root ?
		(numberOfChildren(root) == m) +
		numberOfNodesWithDegreeM(root->firstChild, m) +
		numberOfNodesWithDegreeM(root->sibling, m)
		: 0;
}

bool Tree::containsPosition(Board *b) {
	Node *tmp = root;
	while (tmp) {
		if (*tmp->board == *b)
			return true;
		if (tmp->firstChild)
			tmp = tmp->firstChild;
		else
			tmp = tmp->sibling;
	}
	return false;
}

void Tree::solve() {
	if (!root) return;
	while (!bestSoFar->board->isSolved()) {
		int lastDir = bestSoFar->board->getPrevDir();
		Node *lastChild = nullptr, *nextBest = nullptr;
		int minManhattan = INT_MAX;
		Node *helper = nullptr;
		for (int i = 1; i <= 4; i++) {
			Board *b = bestSoFar->board->slide(i);

			int dir = b->getPrevDir();
			if (dir == 0) {	// no piece has been moved
				delete b;
				continue;
			}
			if ((lastDir == 1 && dir == 2) || (lastDir == 2 && dir == 1) ||
				(lastDir == 3 && dir == 4) || (lastDir == 4 && dir == 3)) {	// we don't want to get the previous position
				delete b;
				continue;
			}

			Node *node = new Node(b);
			if (!lastChild) {
				bestSoFar->firstChild = node;
			} else {
				lastChild->sibling = node;
			}
			lastChild = node;
			if (node->board->isSolved()) {
				bestSoFar = node;
				return;
			}

			if (b->getManhattan() < minManhattan) {
				minManhattan = b->getManhattan();
				nextBest = node;
				//cout << "Manhattan now: " << minManhattan << endl;
			}
			/* else if (!nextBest) {
				helper = node;
			}*/
		}
		/*if (!nextBest) {
			nextBest = helper;
		} else {
			delete helper;
		}*/
		bestSoFar = nextBest;
		cout << *bestSoFar->board;
	}
}

int Tree::height() {
	int *cnt = new int[n], i;
	for (i = 0; i < n; i++) {
		cnt[i] = 0;
	}
	nodesAtLevel(root, cnt, 0);
	for (i = 0; i < n && cnt[i]; i++);
	return i - 1;
}

int Tree::width() {
	int *cnt = new int[n], i;
	for (i = 0; i < n; i++) {
		cnt[i] = 0;
	}
	nodesAtLevel(root, cnt, 0);
	int max = 0;
	for (i = 0; i < n; i++) {
		if (cnt[i] > max) max = cnt[i];
	}
	return max;
}
