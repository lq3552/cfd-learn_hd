/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include "Global.h"
#include <string>
#include <sstream>
#include "SetParameter.h"

int SetParameter(Grid &grid, std::fstream& parameterFile)
{
	// future development: identify optional/compelling parameters
	std::string line;
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
	while ((std::getline(parameterFile, line)) && (comment_count < 2))
	{
		/* Storing the whole line into string stream */
		ReadParameterFromLine<int>(line, "ProblemType", ProblemType);
		ReadParameterFromLine<int>(line, "GridRank", GridRank);
		for (int i = 0; i < MAX_DIMENSION; i++)
			ReadParameterFromLine<int>(line, "GridDimension", GridDimension[i], i + 1);
		ReadParameterFromLine<int>(line, "NumberofGhostZones", NumberofGhostZones);
		ReadParameterFromLine<int>(line, "NumberofBaryonFields", NumberofBaryonFields);
		ReadParameterFromLine<double>(line, "LengthUnit", LengthUnit);
		ReadParameterFromLine<double>(line, "TimeUnit", TimeUnit);
		ReadParameterFromLine<double>(line, "DensityUnit", DensityUnit);
		ReadParameterFromLine<HydroType>(line, "Solver", Solver);
		ReadParameterFromLine<RiemannType>(line, "RiemannSolver", RiemannSolver);
		ReadParameterFromLine<int>(line, "RiemannIteration", RiemannIteration);
		ReadParameterFromLine<BoundaryType>(line, "BoundaryCondition", BoundaryCondition);
		ReadParameterFromLine<int>(line, "EOSType", EOSType);
		ReadParameterFromLine<float>(line, "Gamma", Gamma);
		ReadParameterFromLine<float>(line, "Mu", Mu);
		ReadParameterFromLine<float>(line, "CourantNumber", CourantNumber);
		ReadParameterFromLine<double>(line, "StopTime", StopTime);
		ReadParameterFromLine<int>(line, "StopCycle", StopCycle);
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
