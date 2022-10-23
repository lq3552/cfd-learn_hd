#include "Global.h"
using namespace Types;
#include <fstream>

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
	std::cout << "/* Top grid */\n"
			  << "GridRank: " << GridRank << "\n"
	          << "NumberOfBaryonFields: " << NumberofBaryonFields << std::endl;
	for (int i = 0; i < GridRank; i++)
		std::cout << "GridDimension: " << GridDimension[i];
	std::cout << "\n"
			  << "NumberOfGhostZones: " << NumberofGhostZones << std::endl;
}

int Grid::Output()
{
	// need add a fieldtype identifier!!!!
	std::fstream outputFile;
	outputFile.open("output.txt", std::fstream::out);
	if (!outputFile)
		RETURNFAIL("failed to create an output file");

	int size=1;
	for (int i = 0; i < GridRank; i++)
		size *= GridDimension[i] + 2 * NumberofGhostZones;

	// Note: it's only support 1D for now
	for (int i = NumberofGhostZones; i < size - NumberofGhostZones; i++)
	{
		outputFile << GridData[DensNum][i] << '\t' << GridData[TENum][i] << '\t' << GridData[GENum][i] << '\t' << GridData[Vel1Num][i] << std::endl;
	}

	outputFile.close();
	return SUCCESS;
}
