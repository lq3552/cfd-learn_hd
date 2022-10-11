/* compute time-step */
#include "Global.h"

int Grid::Hydro_TimeStep(double dx, double time, double *cs, double &dt)
{
	int i, size = GridDimension[0] + 2 * NumberofGhostZones;
	double Smax = TINY;
	if (Global::Solver == Types::EXACT)
	{
		for (i = 0; i < size; i++)
			Smax = fmax(Smax, fabs(GridData[Types::Vel1Num][i]) + cs[i]);
		dt = Global::CourantNumber * dx / Smax;
	}
	if (time + dt > Global::StopTime)
		dt = Global::StopTime - time;
	return SUCCESS;
}
