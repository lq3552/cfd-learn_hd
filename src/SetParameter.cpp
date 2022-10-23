/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include "Global.h"

int SetParameter(Grid &grid, FILE* fptr)
{
	// future development: identify optional/compelling parameters, comment, dummy space
	char line[MAX_LINE_LENGTH];
	int ret = 1;
	int comment_count = 0;

	/* Default Global parameters */
	int ProblemType = 0;
	double LengthUnit = 1.0;
	double TimeUnit = 1.0;
	double DensityUnit = 1.0;
	using namespace Types;
	HydroType Solver = HydroType::HD_1ST;
	RiemannType RiemannSolver = RiemannType::EXACT;
	int RiemannIteration = 20;
	BoundaryType BoundaryCondition = BoundaryType::OUTFLOW;
	int EOSType = 1;
	float Gamma = 1.4;
	float Mu = 0.6;
	float CourantNumber = 0.4;
	double StopTime = 1.0;
	int StopCycle = 1000000;
	
	/* Default Top grid parameters */
	int GridRank = 1;
	int GridDimension[MAX_DIMENSION] = {0};
	int NumberofGhostZones = 1;
	int NumberofBaryonFields = 4;

	/* read parameter file */
	while ((fgets(line, MAX_LINE_LENGTH,fptr) != NULL) && (comment_count<2))
	{
		ret = 0;
		/* read parameters */
		ret += sscanf(line,"ProblemType = %d",&ProblemType);
		ret += sscanf(line,"GridRank = %d",&GridRank);
		if (GridRank == 1)
			ret += sscanf(line,"GridDimension = %d",&GridDimension[0]);
		else if (GridRank == 2)
			ret += sscanf(line,"GridDimension = %d %d",&GridDimension[0],&GridDimension[1]);
		else
			ret += sscanf(line,"GridDimension = %d %d %d",&GridDimension[0],&GridDimension[1],&GridDimension[2]);
		ret += sscanf(line,"NumberofGhostZones = %d",&NumberofGhostZones);
		ret += sscanf(line,"NumberofBaryonFields = %d",&NumberofBaryonFields);
		ret += sscanf(line,"LengthUnit = %lf",&LengthUnit);
		ret += sscanf(line,"TimeUnit = %lf",&TimeUnit);
		ret += sscanf(line,"DensityUnit = %lf",&DensityUnit);
		/* Hydro -related parameter */
		ret += sscanf(line,"Solver = %d",&Solver);
		ret += sscanf(line,"RiemannSolver = %d",&RiemannSolver);
		ret += sscanf(line,"RiemannIteration = %d",&RiemannIteration);
		ret += sscanf(line,"BoundaryCondition = %d",&BoundaryCondition); // Here you can see no type safety using plain C I/O, it explains why you should use C++ I/O
		ret += sscanf(line,"EOSType = %d",&EOSType);
		ret += sscanf(line,"Gamma = %f",&Gamma);
		ret += sscanf(line,"Mu = %f",&Mu);
		ret += sscanf(line,"CourantNumber = %f",&CourantNumber);
		ret += sscanf(line,"StopTime = %lf",&StopTime);
		ret += sscanf(line,"StopCycle = %d",&StopCycle);
	}

	Global::SetGlobalParameter(ProblemType,
			             LengthUnit, TimeUnit, DensityUnit,
						 Solver, RiemannSolver, RiemannIteration, BoundaryCondition,
						 EOSType, Gamma, Mu,
						 CourantNumber, StopTime, StopCycle);
	Global::PrintGlobalParameter();

	grid.SetMetaData(GridRank, GridDimension, NumberofGhostZones, NumberofBaryonFields);
	grid.PrintMetaData();

	return SUCCESS;
}
