/* routine for setting boundary values */
#include "Global.h"
#include "typedefs.h"
#include "Grid.h"

int Grid::SetBoundary(double *p, double *cs, double **U){
	/* Purpose: set boundary conditions
	   1 - outflow
	   2 - reflect (currently not supported)
	*/
	int i, n, rear = GridDimension[0] + NumberofGhostZones -1;
	if (BoundaryCondition == Outflow){//outflow
		for (i = 0; i < NumberofGhostZones; i++){
			GridData[DensNum][i] = GridData[DensNum][NumberofGhostZones];
			GridData[TENum][i]   = GridData[TENum][NumberofGhostZones];
			GridData[GENum][i]   = GridData[GENum][NumberofGhostZones];
			GridData[Vel1Num][i] = GridData[Vel1Num][NumberofGhostZones];
			p[i]  = p[NumberofGhostZones];
			cs[i] = cs[NumberofGhostZones];
			for (n = 0; n < GridRank * 3; n++)
				U[n][i] = U[n][NumberofGhostZones];
		}
		for (i = GridDimension[0] + NumberofGhostZones; i < GridDimension[0] + 2 * NumberofGhostZones; i++){
			GridData[DensNum][i] = GridData[DensNum][rear];
			GridData[TENum][i]   = GridData[TENum][rear];
			GridData[GENum][i]   = GridData[GENum][rear];
			GridData[Vel1Num][i] = GridData[Vel1Num][rear];
			p[i] = p[rear];
			cs[i] = cs[rear];
			for (n = 0; n < GridRank * 3; n++)
				U[n][i] = U[n][rear];
		}
	}
	else
		RETURNFAIL("Unsupported boundary condition type!\n");
	return SUCCESS;
}
