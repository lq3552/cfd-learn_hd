/* implementation of Grid class */

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

void Grid::SetMetaData(const int i_GridRank, const int i_GridDimension[], const int i_NumberofGhostZones, const int i_NumberofBaryonFields)
{
	GridRank = i_GridRank;
	for (int i = 0; i < GridRank; i++)
		GridDimension[i] = i_GridDimension[i];
	NumberofGhostZones = i_NumberofGhostZones;
	NumberofBaryonFields = i_NumberofBaryonFields;
}

void Grid::PrintMetaData() const
{
	std::cout << "/* Top grid */" << std::endl
			  << "GridRank: " << GridRank << std::endl;
	for (int i = 0; i < GridRank; i++)
		std::cout << "GridDimension: " << GridDimension[i];
	std::cout << std::endl 
			  << "NumberOfBaryonFields: " << NumberofBaryonFields << std::endl
			  << "NumberOfGhostZones: " << NumberofGhostZones << std::endl;
}

int Grid::Output(int outputNo, std::string suffix) const
{
	// need add a fieldtype identifier!!!!
	std::fstream outputFile;
	std::string no = std::to_string(outputNo);
	no = std::string(4 - no.length(), '0') + no; 
	outputFile.open(static_cast<std::string>(Global::DataDump) + no + suffix, std::fstream::out);
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
