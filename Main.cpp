#include "Tree.h"

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
	/*Tree t(2);
	t.add(1).add(2).add(3).add(4).add(5).add(6).add(7).add(8).add(9).add(10).add(11).add(12).printTree();
	//cout << "Number of nodes: " << t.numberOfNodes();
	cout << "Height: " << t.height() << endl;
	cout << "Width: " << t.width() << endl;
	cout << "Number of nodes with degree m: " << t.numberOfNodesWithDegreeM() << endl;*/

	Board start;
	Tree t;
	t.add(&start);

	while (true) {
		printMenu();

		int choice;
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter starting position: " << endl;
			cin >> start;
			cout << "Enter target position: " << endl;
			Board::loadTarget();
			break;
		case 2:
			start.generate();
			Board::generateTarget();
			cout << start;
			break;
		case 3:

			break;
		case 4:

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