#include <math.h>
#include <stdio.h>
#include "global.h"

int Output(){
	int i;
	int size = GridDimension + 2*NumberofGhostZones;
	FILE *fp;
	if ((fp = fopen("output.txt","w")) == NULL)
		return FAIL;
	for (i = NumberofGhostZones; i < size - NumberofGhostZones; i++){
		fprintf(fp,"%lf\t%lf\t%lf\t%lf\n",Grid[DensNum][i],Grid[TENum][i],Grid[GENum][i],Grid[Vel1Num][i]);
	}
	fclose(fp);
	return SUCCESS;
}
