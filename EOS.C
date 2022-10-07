/* handlers of equation of states */

#include "Global.h"
#include "Grid.h"

//EOS's relation with Grid is a bit messy! improbe it!

int EOS(Grid &grid, double *p,double *cs)
{// Only support ideal gas for now
	int i,size=1;
	for (i = 0; i < grid.GridRank; i++)
		size *= grid.GridDimension[i] + 2 * grid.NumberofGhostZones;
	if (EOSType == 1)
	{ // ideal gas
		for (i = 0; i < size; i++){
			p[i] = grid.GridData[TENum][i] * (Gamma - 1);
			cs[i] = sqrt(Gamma * p[i] / grid.GridData[DensNum][i]);
		}
		return SUCCESS;
	}
	else
		return FAIL;
}

int pEOS(double d, double p, double &e, double &cs)
{// Only support ideal gas for now
	if (EOSType == 1)
	{ // ideal gas
		e = p/(Gamma-1);
		cs = sqrt(Gamma*p/d);
		return SUCCESS;
	}
	else
		return FAIL;
}
