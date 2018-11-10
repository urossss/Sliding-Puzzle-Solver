#include "Tree.h"

int main() {
	Tree t(2);
	t.add(1).add(2).add(3).add(4).add(5).add(6).add(7).add(8).add(9).add(10).add(11).add(12).printTree();
	//cout << "Number of nodes: " << t.numberOfNodes();
	cout << "Height: " << t.height() << endl;
	cout << "Width: " << t.width() << endl;
	cout << "Number of nodes with degree m: " << t.numberOfNodesWithDegreeM() << endl;
}