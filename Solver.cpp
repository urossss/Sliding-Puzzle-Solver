#include "Solver.h"
#include "List.h"
#include "PriorityQueue.h"


Board* Solver::solveAStar(Board *start) {
	//cout << "started...\n";
	PriorityQueue open;
	List closed;

	open.insert(start);

	while (!open.empty()) {
		Board *curr = open.remove();

		if (curr->g() > 50) {	// should be 32, that's the maximum number of moves required to solve any possible combnation
			cout << "Iteration error.\n";
			return nullptr;
		}

		if (curr->isSolved()) {
			cout << "Success!\n";
			return curr;
		}

		closed.add(curr);

		for (int i = 1; i <= 4; i++) {	// generating all children of curr
			Board *child = curr->slide(i);
			if (child->getPrevDir() == 0) continue;

			//cout << *child;
			//cout << child->getManhattan() << endl << endl;

			bool isInOpen = open.contains(child);
			bool isInClosed = closed.contains(child);

			if (!isInOpen && !isInClosed) {
				open.insert(child);
			} else if (isInOpen) {
				Board *tmp = open.remove(child);
				if (tmp->g() > child->g()) {	// the one in open list was reached by a longer path
					open.insert(child);
				} else {
					open.insert(tmp);
				}
			} else if (isInClosed) {
				Board *tmp = closed.remove(child);
				if (tmp->g() > child->g()) {	// the one in closed list was reached by a longer path
					open.insert(child);
				} else {
					closed.add(tmp);
				}
			}
		}

		
	}
	//cout << "Failure!\n";
	return nullptr;
}
