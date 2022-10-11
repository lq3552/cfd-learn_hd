/* Methods for initialization of grid data */

#include "Global.h"
using namespace Types;
#include "EOS.h"

Grid::GridInitializer::GridInitializer(Grid &grid) : grid(grid) {}

int Grid::GridInitializer::AllocateGrid()
{
	int size = 1; 
	for (int i = 0; i < grid.GridRank; i++)
		size *= grid.GridDimension[i] + 2 * grid.NumberofGhostZones;
	try
	{
		grid.GridData = new double*[grid.NumberofBaryonFields];
		for (int i = 0; i < grid.NumberofBaryonFields; i++)
		{
			grid.GridData[i] = new double[size];
			for (int j = 0; j < size; j++)
				grid.GridData[i][j] = 0.0;
		}
	}
	catch(exception &e)
	{
		printf("Nuke detected!\n");
		return FAIL;
	}

	return SUCCESS;
}

void Grid::GridInitializer::AssignPrimitive(double (&w)[4], double d, double u, double p)
{
	w[0] = d;
	w[1] = u;
	w[2] = p;
}

int Grid::GridInitializer::TestInitialize(int setNo)
{ 
	if(AllocateGrid() != SUCCESS)
	{
		RETURNFAIL("failed to allocate memories to grid");
	}
	
	double wL[4], wR[4]; // density, velocity, pressure, specific internal energy
	double cs; // placeholder
	double fractionLeft; // length of left / total length
	switch(setNo)
	{
		case 0: // shock tube
			AssignPrimitive(wL, 1.0, 0.75, 1.0);
			AssignPrimitive(wR, 0.125, 0.0, 0.1);
			Global::StopTime = 0.20;
			fractionLeft = 0.3;
			break;
		case 1: // rarefaction
			AssignPrimitive(wL, 1.0, -2.0, 0.4);
			AssignPrimitive(wR, 1.0, 2.0, 0.4);
			Global::StopTime = 0.15;
			fractionLeft = 0.5;
			break;
		case 2: // expansion
			AssignPrimitive(wL, 1.0, 0.0, 1000.0);
			AssignPrimitive(wR, 1.0, 0.0, 0.01);
			Global::StopTime = 0.012;
			fractionLeft = 0.5;
			break;
		case 3: // mixing
			AssignPrimitive(wL, 5.99924, 19.5975, 460.894);
			AssignPrimitive(wR, 5.99242, -6.19633, 46.095);
			Global::StopTime = 0.035;
			fractionLeft = 0.4;
			break;
		case 4: // expansion + Galilean transformation
			AssignPrimitive(wL, 1.0, -19.59745, 1000.0);
			AssignPrimitive(wR, 1.0, -19.59745, 0.01);
			Global::StopTime = 0.012;
			fractionLeft = 0.8;
			break;
		default:
			RETURNFAIL("unsupported test problem");
	}
	pEOS(wL[0], wL[2], wL[3], cs);
	pEOS(wR[0], wR[2], wR[3], cs);

	for (int i = grid.NumberofGhostZones; i < grid.GridDimension[0] + grid.NumberofGhostZones; i++)
	{
		if (i <= fractionLeft * grid.GridDimension[0])
		{
			grid.GridData[DensNum][i] = wL[0];
			grid.GridData[Vel1Num][i] = wL[1];
			grid.GridData[GENum][i] = wL[3];
			grid.GridData[TENum][i] = wL[3] + 0.5 * wL[0] * wL[1] * wL[1];
		}
		else
		{
			grid.GridData[DensNum][i] = wR[0];
			grid.GridData[Vel1Num][i] = wR[1];
			grid.GridData[GENum][i] = wR[3];
			grid.GridData[TENum][i] = wR[3] + 0.5 * wR[0] * wR[1] * wR[1];
		}
	}

	return SUCCESS;
}
