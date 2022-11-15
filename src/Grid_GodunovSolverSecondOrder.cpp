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

void Grid::GodunovSolverSecondOrder::ReconstructInterface(int i, double* const W, double &c, int sign = 1)
{
	/* i-1 i i+1 */
	/* <-a   a-> */
	W[0] = d[i] + 0.5 * sign * vanLeer(i, d);
	W[1] = u[i] + 0.5 * sign * vanLeer(i, u);
	W[2] = p[i] + 0.5 * sign * vanLeer(i, p);
	c  = cs[i] + 0.5 * sign * vanLeer(i, cs);
}

double Grid::GodunovSolverSecondOrder::VanLeer(int i, double *q)
{
	double dL = q[i] - q[i - 1];
	double dR = q[i + 1] - q[i];
	return dL * dR > 0 ? 2.0 / (1.0 / dL + 1.0 / dR) : 0;
}
