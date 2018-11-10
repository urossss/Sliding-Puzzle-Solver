#include "Tree.h"


Tree& Tree::add(Board *b) {
	Node *tmp = new Node(b);
	if (!root) {
		root = tmp;
	} else {
		Node *node = nodeWithLessThenMChildren(root, m);
		if (!node) exit(1);
		if (!node->firstChild) {
			node->firstChild = tmp;
		} else {
			Node *child = node->firstChild;
			while (child->sibling) {
				child = child->sibling;
			}
			child->sibling = tmp;
		}
	}
	n++;
	return *this;
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
			cout << child->board << "*****" << endl;
			child = child->sibling;
		}
		cout << endl;
	}
}

void Tree::preorderPrint(Node *root) {	// prints all nodes in preorder, one node (with its children) per line
	if (root) {
		cout << *root->board;
		printChildren(root);

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
