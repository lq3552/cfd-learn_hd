#include "Global.h"
using namespace Types;

Grid::~Grid() // it is not needed for a hydro solver structured like ours; just for learning
{
	/* garbage collection */
	for (int i = 0; i < NumberofBaryonFields; i++)
	{
		delete[] GridData[i];
	}
	delete[] GridData;
}

void Grid::SetMetaData(int i_GridRank,int i_GridDimension[],int i_NumberofGhostZones,int i_NumberofBaryonFields)
{
	GridRank = i_GridRank;
	for (int i = 0; i < GridRank; i++)
		GridDimension[i] = i_GridDimension[i];
	NumberofGhostZones = i_NumberofGhostZones;
	NumberofBaryonFields = i_NumberofBaryonFields;
}

void Grid::PrintMetaData()
{
	printf("/* Top grid */\n");
	printf("GridRank: %d\n", GridRank);
	printf("NumberOfBaryonFields: %d\n", NumberofBaryonFields);
	for (int i = 0; i < GridRank; i++)
		printf("GridDimension: %d ", GridDimension[i]);
	printf("\n");
	printf("NumberOfGhostZones: %d\n", NumberofGhostZones);
}

int Grid::Output()
{
	// need add a fieldtype identifier!!!!
	int size=1;
	FILE *fp;
	for (int i = 0; i < GridRank; i++)
		size *= GridDimension[i] + 2 * NumberofGhostZones;
	if ((fp = fopen("output.txt","w")) == NULL)
		return FAIL;
	// Note: it's only support 1D for now
	for (int i = NumberofGhostZones; i < size - NumberofGhostZones; i++){
		fprintf(fp,"%lf\t%lf\t%lf\t%lf\n",GridData[DensNum][i], GridData[TENum][i], GridData[GENum][i] , GridData[Vel1Num][i]);
	}
	fclose(fp);
	return SUCCESS;
}
