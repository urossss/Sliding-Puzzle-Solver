#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "Board.h"

class Solver {
public:
	static Board* solveAStar(Board *start);
};

#endif