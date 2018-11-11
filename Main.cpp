#include "Tree.h"
#include <ctime>

void printMenu() {
	cout << endl;
	cout << "Choose one of the following commands:" << endl;
	cout << "    1. Enter starting and target position manually" << endl;
	cout << "    2. Generate starting and target position automatically" << endl;
	cout << "    3. Check whether puzzle is solvable" << endl;
	cout << "    4. Solve a puzzle" << endl;
	cout << "    0. Exit" << endl;
	cout << "Your choice: ";
}

int main() {

	Board *start = new Board;
	Tree t(4);
	t.add(start);

	srand(time(NULL));

	while (true) {
		printMenu();

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			t.deleteTree();
			start = new Board;
			t.add(start);
			cout << "Enter starting position: " << endl;
			cin >> *start;
			cout << "Enter target position: " << endl;
			Board::loadTarget();
			cout << start->isSolvable() << endl;
			break;
		case 2:
			t.deleteTree();
			start = new Board;
			t.add(start);
			start->generate();
			Board::generateTarget();
			cout << *start;
			Board::printTarget();
			break;
		case 3:
			if (start->isSolvable())
				cout << "The puzzle is solvable." << endl;
			else
				cout << "The puzzle is not solvable." << endl;
			break;
		case 4:
			if (start->isSolvable()) {
				t.solve();
				//t.printTree();
			} else
				cout << "The puzzle is not solvable." << endl;
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Invalid choice! Try again." << endl;
			break;
		}
	}
}