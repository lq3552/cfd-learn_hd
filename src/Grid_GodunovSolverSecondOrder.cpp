/* PLM reconstruction */

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
	W[0] = d[i] + 0.5 * sign * VanLeer(i, d);
	W[1] = u[i] + 0.5 * sign * VanLeer(i, u);
	W[2] = p[i] + 0.5 * sign * VanLeer(i, p);
	c  = cs[i] + 0.5 * sign * VanLeer(i, cs);
}

double Grid::GodunovSolverSecondOrder::VanLeer(int i, double *q)
{
	double dL = q[i] - q[i - 1];
	double dR = q[i + 1] - q[i];
	return dL * dR > 0 ? 2.0 / (1.0 / dL + 1.0 / dR) : 0;
}
