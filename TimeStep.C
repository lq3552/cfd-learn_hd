/* compute time-step */
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "typedefs.h"
#include "grid.h"

int Hydro_TimeStep(double dx, double time, double *u, double *cs, double &dt,int GridRank,int* GridDimension,int NumberofGhostZones){
	int i,size = GridDimension[0] + 2*NumberofGhostZones;
	double Smax = TINY;
	if (Solver == exact){
		for (i = 0; i < size; i++)
			Smax = fmax(Smax,fabs(u[i]) + cs[i]);
		dt = CourantNumber*dx/Smax;
	}
	if (time + dt > StopTime)
		dt = StopTime - time;
	return SUCCESS;
}
