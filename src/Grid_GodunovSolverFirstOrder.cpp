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

void Grid::GodunovSolverFirstOrder::ReconstructInterface(int i, double* const WL, double* const WR, double &cL, double &cR)
{
	WL[0] = d[i];
	WL[1] = u[i];
	WL[2] = p[i];
	cL = cs[i];
	WR[0] = d[i + 1];
	WR[1] = u[i + 1];
	WR[2] = p[i + 1];
	cR = cs[i + 1];
}
