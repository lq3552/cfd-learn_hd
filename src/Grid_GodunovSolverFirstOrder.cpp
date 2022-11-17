/* PCM reconstruction */

#include "Global.h"
using namespace Types;
#include "EOS.h"
#include "RiemannSolver.h"

Grid::GodunovSolverFirstOrder::GodunovSolverFirstOrder(Grid &grid) : Grid::GodunovSolver(grid)
{
}

void Grid::GodunovSolverFirstOrder::ReconstructInterface(int i, double* const W, double& c, int sign)
{
	W[0] = d[i];
	W[1] = u[i];
	W[2] = p[i];
	c = cs[i];
}
