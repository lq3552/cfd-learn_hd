/* handlers of equation of states */

#include "Global.h"
using namespace Types;

//EOS's relation with Grid is a bit messy! improbe it!

int EOS(Grid &grid, double *p,double *cs)
{// Only support ideal gas for now
	int size=1;
	for (int i = 0; i < grid.GridRank; i++)
		size *= grid.GridDimension[i] + 2 * grid.NumberofGhostZones;
	if (Global::EOSType == 1)
	{ // ideal gas
		for (int i = 0; i < size; i++)
		{
			p[i] = grid.GridData[TENum][i] * (Global::Gamma - 1);
			cs[i] = sqrt(Global::Gamma * p[i] / grid.GridData[DensNum][i]);
		}
		return SUCCESS;
	}
	else
		return FAIL;
}

int pEOS(double d, double p, double &e, double &cs)
{// Only support ideal gas for now
	if (Global::EOSType == 1)
	{ // ideal gas
		e = p / (Global::Gamma - 1.0);
		cs = sqrt(Global::Gamma * p / d);
		return SUCCESS;
	}
	else
		return FAIL;
}
