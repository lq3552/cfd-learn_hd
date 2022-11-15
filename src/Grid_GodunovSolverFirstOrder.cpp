/* Evolve Euler equations with Godunov Upwind Scheme
   written by: Qi Li
   Version: 1.0
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Nov 27, 2016 */

#include "Global.h"
using namespace Types;
#include "EOS.h"
#include "RiemannSolver.h"

Grid::GodunovSolverFirstOrder::GodunovSolverFirstOrder(Grid &grid) : Grid::GodunovSolver(grid)
{
}

void Grid::GodunovSolverFirstOrder::ReconstructInterface(int i, double* const W, double& c, int sign = 1)
{
	W[0] = d[i];
	W[1] = u[i];
	W[2] = p[i];
	c = cs[i];
}
