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

void Grid::GodunovSolverSecondOrder::ReconstructInterface(int i, double* const WL, double* const WR, double &cL, double &cR)
{
	/* i-1 i i+1 */
	/* <-a   a-> */
	int id; 
	int j = i + 1;
	//double dummy;

	id = u[i] + cs[i] > 0 ? i : i + 1;
	WL[0] = d[i] + (d[id] - d[id - 1]) / 2.0;
	WL[1] = u[i] + (u[id] - u[id - 1]) / 2.0;
	WL[2] = p[i] + (p[id] - p[id - 1]) / 2.0;
	cL = cs[i] + (cs[id] - cs[id - 1]) / 2.0;
	id = u[j] + cs[j] > 0 ? j : j  + 1;
	WR[0] = d[j] - (d[id] - d[id - 1]) / 2.0;
	WR[1] = u[j] - (u[id] - u[id - 1]) / 2.0;
	WR[2] = p[j] - (p[id] - p[id - 1]) / 2.0;
	cR = cs[j] - (cs[id] - cs[id - 1]) / 2.0;
	/*WL[1] = (d[i] * u[i] + (u[i + 1] * d[i + 1] - u[i] * d[i]) / 2.0) / WL[0];
	WL[2] = p[i] + (p[i + 1] - p[i]) / 2.0;
	pEOS(WL[0], WL[2], dummy, cL);
	WR[0] = d[i + 1] + (d[i + 2] - d[i + 1]) / 2.0;
	WR[1] = (d[i + 1] * u[i + 1] + (u[i + 2] * d[i + 2] - u[i + 1] * d[i + 1]) / 2.0) / WR[0];
	WR[2] = p[i + 1] + (p[i + 2] - p[i + 1]) / 2.0;
	pEOS(WR[0], WR[2], dummy, cR); */
};
