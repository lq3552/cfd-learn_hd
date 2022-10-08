#include "Global.h"
#include "Grid.h"

void Grid::SetMetaData(int m_GridRank,int m_GridDimension[],int m_NumberofGhostZones,int m_NumberofBaryonFields)
{
	GridRank = m_GridRank;
	for (int i = 0; i < GridRank; i++)
		GridDimension[i] = m_GridDimension[i];
	NumberofGhostZones = m_NumberofGhostZones;
	NumberofBaryonFields = m_NumberofBaryonFields;
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
