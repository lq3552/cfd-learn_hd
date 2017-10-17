/* routine for setting boundary values */
#include <math.h>
#include <stdio.h>
#include "global.h"
#include "typedefs.h"
#include "grid.h"

int Boundary(double *d, double *E, double *e, double *u, double *p, double *cs, double **U,int GridRank,int* GridDimension,int NumberofGhostZones){
	/* Purpose: set boundary conditions
	   1 - outflow
	   2 - reflect (currently not supported)
	*/
	int i,n,rear = GridDimension[0] + NumberofGhostZones -1;
	if (BoundaryCondition == outflow){//outflow
		for (i = 0; i < NumberofGhostZones; i++){
			d[i] = d[NumberofGhostZones];
			E[i] = E[NumberofGhostZones];
			e[i] = e[NumberofGhostZones];
			u[i] = u[NumberofGhostZones];
			p[i] = p[NumberofGhostZones];
			cs[i] = cs[NumberofGhostZones];
			for (n = 0; n < GridRank*3; n++)
				U[n][i] = U[n][NumberofGhostZones];
		}
		for (i = GridDimension[0] + NumberofGhostZones; i < GridDimension[0] + 2*NumberofGhostZones; i++){
			d[i] = d[rear];
			E[i] = E[rear];
			e[i] = e[rear];
			u[i] = u[rear];
			p[i] = p[rear];
			cs[i] = cs[rear];
			for (n = 0; n < GridRank*3; n++)
				U[n][i] = U[n][rear];
		}
	}
	else
		RETURNFAIL("Unsupported boundary condition type!\n");
	return SUCCESS;
}
