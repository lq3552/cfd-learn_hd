#include <stdio.h>
#include "global.h"
#include "grid.h"

int grid::Output(){
	// need add a fieldtype identifier!!!!
	int i,size=1;
	FILE *fp;
	for (i = 0; i < GridRank; i++)
		size *= GridDimension[i] + 2*NumberofGhostZones;
	if ((fp = fopen("output.txt","w")) == NULL)
		return FAIL;
	// Note: it's only support 1D for now, I will correct it later
	for (i = NumberofGhostZones; i < size - NumberofGhostZones; i++){
		fprintf(fp,"%lf\t%lf\t%lf\t%lf\n",Grid[0][i],Grid[1][i],Grid[2][i],Grid[3][i]);
	}
	fclose(fp);
	return SUCCESS;
}
