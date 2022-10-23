/* Evolve Euler equations with second-order Godunov Scheme
   written by: Qi Li
   Version: 0.0
             -- no implementation yet
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Oct 23, 2022 */

#include "Global.h"
using namespace Types;
#include "EOS.h"
#include "RiemannSolver.h"

Grid::GodunovSolverSecondOrder::GodunovSolverSecondOrder(Grid &grid) : Grid::GodunovSolver(grid)
{
}

int Grid::GodunovSolverSecondOrder::EvolveGodunov()
{
	/* Second-order Godunov Solver */
	std::cout << "Second-order Godunov scheme computation complete!" << std::endl;
	return SUCCESS;
}

int Grid::GodunovSolverSecondOrder::ComputeFlux()
{
	return SUCCESS;
}
