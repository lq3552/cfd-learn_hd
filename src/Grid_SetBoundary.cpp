/* routine for setting boundary values */
#include "Global.h"
using namespace Types;

int Grid::SetBoundary(double *p, double *cs, double **U)
{
	/* Purpose: set boundary conditions
	   1 - outflow
	   2 - reflect (currently not supported)
	*/
	int rear = GridDimension[0] + NumberofGhostZones -1;
	if (Global::BoundaryCondition == BoundaryType::OUTFLOW)
	{	// outflow
		for (int i = 0; i < NumberofGhostZones; i++)
			SetGhostValue(i, NumberofGhostZones, p, cs, U);
		for (int i = GridDimension[0] + NumberofGhostZones; i < GridDimension[0] + 2 * NumberofGhostZones; i++)
			SetGhostValue(i, rear, p, cs, U);
	}
	else
		RETURNFAIL("Unsupported boundary condition type!");
	return SUCCESS;
}

void Grid::SetGhostValue(int i, int i_bound, double *p, double *cs, double **U)
{
	switch(Global::BoundaryCondition)
	{
		case BoundaryType::OUTFLOW:
			GridData[DensNum][i] = GridData[DensNum][i_bound];
			GridData[TENum][i]   = GridData[TENum][i_bound];
			GridData[GENum][i]   = GridData[GENum][i_bound];
			GridData[Vel1Num][i] = GridData[Vel1Num][i_bound];
			p[i]  = p[i_bound];
			cs[i] = cs[i_bound];
			for (int n = 0; n < GridRank * 3; n++)
				U[n][i] = U[n][i_bound];
			return;
		default:
			return;
	}
}
