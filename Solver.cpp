#include "Solver.h"
#include "List.h"
#include "PriorityQueue.h"


Board* Solver::solveAStar(Board *start) {
	PriorityQueue open;		// positions that are yet to be processed
	List closed;			// processed position

	open.insert(new Board(*start));

	while (!open.empty()) {
		Board *curr = open.remove();

		if (curr->g() > 50) {	// should be 32, that's the maximum number of moves required to solve any possible combnation, but this is empirical
			cout << "Iteration error.\n";
			return nullptr;
		}

		if (curr->isSolved()) {
			return Board::copySolution(curr);
		}

		closed.add(curr);

		for (int i = 1; i <= 4; i++) {	// generating all children of curr
			Board *child = curr->slide(i);
			if (child->getPrevDir() == 0) continue;

			bool isInOpen = open.contains(child);
			bool isInClosed = closed.contains(child);

			if (!isInOpen && !isInClosed) {
				open.insert(child);
			} else if (isInOpen) {
				Board *tmp = open.remove(child);
				if (tmp->g() > child->g()) {	// the one in open list was reached by a longer path
					open.insert(child);
					delete tmp;
				} else {
					open.insert(tmp);
					delete child;
				}
			} else if (isInClosed) {
				Board *tmp = closed.remove(child);
				if (tmp->g() > child->g()) {	// the one in closed list was reached by a longer path
					open.insert(child);
					delete tmp;
				} else {
					closed.add(tmp);
					delete child;
				}
			}
		}
	}
	return nullptr;
}
