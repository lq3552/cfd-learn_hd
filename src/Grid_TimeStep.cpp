/* compute time-step */

#include "Global.h"

double Grid::GodunovSolver::SetTimeStep() const
{
	int i, size = grid.GridDimension[0] + 2 * grid.NumberofGhostZones;
	double Smax = TINY;
	double dtTemp = -1.0;

	if (Global::RiemannSolver == Types::RiemannType::EXACT)
	{
		for (i = 0; i < size; i++)
			Smax = fmax(Smax, fabs(grid.GridData[Types::Vel1Num][i]) + cs[i]);
		dtTemp = Global::CourantNumber * dx / Smax;
	}

	double timeLimit = fmin(Global::StopTime, timeNextOutput);
	if (time + dtTemp > timeLimit)
		dtTemp = timeLimit - time;

	return dtTemp;
}
