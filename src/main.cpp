/* Main function, control the root level problem solution process
   Author : Qi Li (pg3552@ufl.edu)
   create : Nov. 27, 2016 
   Update1: Oct. 16, 2017
 */

#include "Global.h"
#include <fstream>

int main(int argc, char *argv[])
{
	Grid grid;
	FILE *fptr;

	if (argc > 1)
	{
		std::cout << "Reading parameter file to set global parameters..." << std::endl;
		if ((fptr = fopen(argv[1],"r")) == NULL)
			RETURNFAIL("failed to open parameter file!");
		if (SetParameter(grid, fptr) != SUCCESS)
			RETURNFAIL("failed to set global parameters from file!");
		std::cout << "Setting parameters succeeds!" << std::endl;
	}
	else
	{
		RETURNFAIL("please provide the parameter file: (EXE) PATH_TO_PARAMETER_FILE");
	}

	if (Grid::GridInitializer(grid).TestInitialize(Global::ProblemType) != SUCCESS)
		RETURNFAIL("failed to initialize problem!");

	switch (Global::Solver)
	{
		case Types::HydroType::HD_1ST: 
			if (Grid::GodunovSolverFirstOrder(grid).EvolveGodunov() != SUCCESS)
				RETURNFAIL("failure in first-order Godunov solver!");
			break;
		case Types::HydroType::HD_2ND: 
			if (Grid::GodunovSolverSecondOrder(grid).EvolveGodunov() != SUCCESS)
				RETURNFAIL("failure in second-order Godunov solver!");
			break;
		default:
			RETURNFAIL("unsupported solver!");
	}

	if (grid.Output() != SUCCESS)
		RETURNFAIL("failed to output!");

	return SUCCESS;
}
