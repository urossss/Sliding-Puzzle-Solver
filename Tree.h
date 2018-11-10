#ifndef _TREE_H_
#define _TREE_H_

#include "Queue.h"
#include <iostream>
using namespace std;

class Tree {
	struct Node {
		int value;
		Node *firstChild, *sibling;
		Node(int v, Node *l = nullptr, Node *r = nullptr) {
			value = v;
			firstChild = l;
			sibling = r;
		}
	};
	int m, n;	// degree and number of nodes
	Node *root;
public:
	Tree(int degree = 2) {	// creating an empty tree
		m = degree;
		n = 0;
		root = nullptr;
	}
	~Tree() {				// destructor
		deleteTree(root);
	}
	Tree& add(int x);
	void printTree() {
		preorderPrint(root);
	}
	void deleteTree() {		// deleting a tree
		deleteTree(root);
		n = 0;
	}

	// extra features
	int height();
	int width();
	int numberOfNodesWithDegreeM() {
		return numberOfNodesWithDegreeM(root, m);
	}
	int numberOfNodes() {
		return n;
	}
private:
	static void deleteTree(Node *root);
	static int numberOfChildren(Node *root);
	static Node* nodeWithLessThenMChildren(Node *root, int m);
	static void printChildren(Node *root);
	static void preorderPrint(Node *root);
	static void nodesAtLevel(Node *root, int *cnt, int level);
	static int numberOfNodesWithDegreeM(Node *root, int m);
};

#endif