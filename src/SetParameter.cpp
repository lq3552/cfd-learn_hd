/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include "Global.h"
using namespace Types;
#include <sstream>
#include <vector>
#include <map>
#include "SetParameter.h"

int InitializeKeywordChecklist(std::map<std::string, int>& checklist, const std::vector<std::string> keywords);
int CheckKeyword(const std::map<std::string, int> checklist, const int);

int SetParameter(Grid &grid, std::fstream& parameterFile)
{
	/* structures to handle keywords */
	const std::vector<std::string> keywords {"ProblemType", "LengthUnit", "TimeUnit", "DensityUnit",
		"Solver", "RiemannSolver", "RiemannIteration", "BoundaryCondition",
		"EOSType", "Gamma", "Mu", "CourantNumber", "StopTime", "StopCycle",
		"DataDump", "dtDump",
		"GridRank", "GridDimension", "NumberofGhostZones", "NumberofBaryonFields"};
	std::map <std::string, int> keywordChecklist;
	if(InitializeKeywordChecklist(keywordChecklist, keywords) != SUCCESS)
		RETURNFAIL("failed to initialize keyword checklist!");

	/* Default Global parameters */
	int ProblemType;
	double LengthUnit;
	double TimeUnit;
	double DensityUnit;
	HydroType Solver;
	RiemannType RiemannSolverType;
	int RiemannIteration;
	BoundaryType BoundaryCondition;
	int EOSType;
	float Gamma;
	float Mu;
	float CourantNumber;
	double StopTime;
	int StopCycle;
	std::string DataDump;
	double dtDump = -1.0;
	
	/* Default Top grid parameters */
	int GridRank = -1;
	int GridDimension[MAX_DIMENSION];
	int NumberofGhostZones;
	int NumberofBaryonFields;

	/* read parameter file */
	std::string line;
	while (std::getline(parameterFile, line))
	{
		/* Storing the whole line into string stream */
		ReadParameterFromLine<int>(line, keywords[0], ProblemType, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[1], LengthUnit, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[2], TimeUnit, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[3], DensityUnit, keywordChecklist);
		ReadParameterFromLine<HydroType>(line, keywords[4], Solver, keywordChecklist);
		ReadParameterFromLine<RiemannType>(line, keywords[5], RiemannSolverType, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[6], RiemannIteration, keywordChecklist);
		ReadParameterFromLine<BoundaryType>(line, keywords[7], BoundaryCondition, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[8], EOSType, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[9], Gamma, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[10], Mu, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[11], CourantNumber, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[12], StopTime, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[13], StopCycle, keywordChecklist);
		ReadParameterFromLine<std::string>(line, keywords[14], DataDump, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[15], dtDump, keywordChecklist);

		ReadParameterFromLine<int>(line, keywords[16], GridRank, keywordChecklist);
		for (int i = 0; i < MAX_DIMENSION; i++)
			ReadParameterFromLine<int>(line, keywords[17], GridDimension[i], keywordChecklist, i + 1);
		ReadParameterFromLine<int>(line, keywords[18], NumberofGhostZones, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[19], NumberofBaryonFields, keywordChecklist);
	}
	if(CheckKeyword(keywordChecklist, GridRank) != SUCCESS)
		RETURNFAIL("one or more parameters are missing!");

	Global::SetGlobalParameter(ProblemType,
			             LengthUnit, TimeUnit, DensityUnit,
						 Solver, RiemannSolverType, RiemannIteration, BoundaryCondition,
						 EOSType, Gamma, Mu,
						 CourantNumber, StopTime, StopCycle,
						 DataDump, dtDump);
	Global::PrintGlobalParameter();

	RiemannSolver::ComputeGammaParam();

	grid.SetMetaData(GridRank, GridDimension, NumberofGhostZones, NumberofBaryonFields);
	grid.PrintMetaData();

	return SUCCESS;
}

int InitializeKeywordChecklist(std::map<std::string, int>& checklist, const std::vector<std::string> keywords)
{
	for (auto i = keywords.begin(); i != keywords.end(); i++)
	{
		checklist[*i] = 0;
	}
	return SUCCESS;
}

int CheckKeyword(const std::map<std::string, int> checklist, const int GridRank)
{
	int numMissing = 0;
	if (GridRank <= 0)
	{
		numMissing++;
		std::cerr << "ERROR: missing parameter: GridRank!" << std::endl;
	}
	for (auto i = checklist.begin(); i != checklist.end(); i++)
	{
		if (i->first == "dtDump" && i->second != 1)
		{
			std::cout << "WARNING: missing parameter: dtDump. dtDump is set to StopTime!" << std::endl;
		}
		else if (i->first != "GridRank" && i->first != "GridDimension" && i->second != 1)
		{
			numMissing++;
			std::cerr << "ERROR: missing parameter: " << i->first << " !" << std::endl;
		}
		else
		{
			if (GridRank > 0 && i->second != GridRank)
			{
				numMissing++;
				std::cerr << "ERROR: missing parameter: "  << i->first << " should have " << GridRank << " element(s)!" << std::endl;
			}
		}
	}
	if (numMissing)
		return FAIL;
	return SUCCESS;
}
