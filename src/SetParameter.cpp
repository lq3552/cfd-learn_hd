/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include "Global.h"
using namespace Types;
#include <string>
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
		"GridRank", "GridDimension", "NumberofGhostZones", "NumberofBaryonFields"};
	std::map <std::string, int> keywordChecklist;
	if(InitializeKeywordChecklist(keywordChecklist, keywords) != SUCCESS)
		RETURNFAIL("failed to initialize keyword checklist!");

	/* Default Global parameters */
	int ProblemType = 0;
	double LengthUnit = 1.0;
	double TimeUnit = 1.0;
	double DensityUnit = 1.0;
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
	std::string line;
	while (std::getline(parameterFile, line))
	{
		/* Storing the whole line into string stream */
		ReadParameterFromLine<int>(line, keywords[0], ProblemType, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[1], LengthUnit, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[2], TimeUnit, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[3], DensityUnit, keywordChecklist);
		ReadParameterFromLine<HydroType>(line, keywords[4], Solver, keywordChecklist);
		ReadParameterFromLine<RiemannType>(line, keywords[5], RiemannSolver, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[6], RiemannIteration, keywordChecklist);
		ReadParameterFromLine<BoundaryType>(line, keywords[7], BoundaryCondition, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[8], EOSType, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[9], Gamma, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[10], Mu, keywordChecklist);
		ReadParameterFromLine<float>(line, keywords[11], CourantNumber, keywordChecklist);
		ReadParameterFromLine<double>(line, keywords[12], StopTime, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[13], StopCycle, keywordChecklist);

		ReadParameterFromLine<int>(line, keywords[14], GridRank, keywordChecklist);
		for (int i = 0; i < MAX_DIMENSION; i++)
			ReadParameterFromLine<int>(line, keywords[15], GridDimension[i], keywordChecklist, i + 1);
		ReadParameterFromLine<int>(line, keywords[16], NumberofGhostZones, keywordChecklist);
		ReadParameterFromLine<int>(line, keywords[17], NumberofBaryonFields, keywordChecklist);
	}
	if(CheckKeyword(keywordChecklist, GridRank) != SUCCESS)
		RETURNFAIL("one or more parameters are missing!");

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
	for (auto i = checklist.begin(); i != checklist.end(); i++)
	{
		if (i->first != "GridDimension")
		{
			if (i->second != 1)
			{
				numMissing++;
				std::cerr << "missing parameter: " << i->first << " !" << std::endl;
			}
		}
		else
		{
			if (i->second != GridRank)
			{
				numMissing++;
				std::cerr << "missing parameter: "  << i->first << " should have " << GridRank << " element(s)!" << std::endl;
			}
		}
	}
	if (numMissing)
		return FAIL;
	return SUCCESS;
}
