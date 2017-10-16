/* Initialize Grid data array*/

#include <stdio.h>
#include "global.h"
#include "grid.h"

void grid::AllocateGrid(){
	int size = 1,i,j; 
	for (i = 0; i < GridRank; i++)
		size *= GridDimension[i] + 2*NumberofGhostZones;
	Grid = new double*[NumberofBaryonFields];
	for (i = 0; i < NumberofBaryonFields; i++){
		Grid[i] = new double[size];
		for (j = 0; j < size; j++)
			Grid[i][j] = 0.0;
	}
}
