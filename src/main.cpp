/* Main function, control the root level problem solution process
   Author : Qi Li (pg3552@ufl.edu)
   create : Nov. 27, 2016 
   Update1: Oct. 16, 2017
 */

#include "Global.h"

int main(int argc, char *argv[])
{
	Grid grid;
	std::fstream parameterFile;

	if (argc > 1)
	{
		std::cout << "Reading parameter file to set global parameters..." << std::endl;
		parameterFile.open(argv[1], std::fstream::in);
		if (!parameterFile)
			RETURNFAIL("failed to open parameter file!");
		if (SetParameter(grid, parameterFile) != SUCCESS)
			RETURNFAIL("failed to set global parameters from file!");
		std::cout << "Setting parameters succeeds!" << std::endl;
	}
	else
	{
		RETURNFAIL("please provide the parameter file: (EXE) PATH_TO_PARAMETER_FILE");
	}

	if (Grid::GridInitializer(grid).TestInitialize(Global::ProblemType) != SUCCESS)
		RETURNFAIL("failed to initialize problem!");

	Grid::GodunovSolver *godunov;
	switch (Global::Solver)
	{
		case Types::HydroType::HD_1ST: 
			if (!(godunov = new Grid::GodunovSolverFirstOrder(grid)))
				RETURNFAIL("failed to initialize 1st-order Godunov solver!");
			break;
		case Types::HydroType::HD_2ND: 
			if (!(godunov = new Grid::GodunovSolverSecondOrder(grid)))
				RETURNFAIL("failed to initialize 2nd-order Godunov solver!");
			break;
		default:
			RETURNFAIL("unsupported solver!");
	}
	if((godunov -> EvolveGodunov()!= SUCCESS))
		RETURNFAIL("failed to evolve the grid!");

	if (grid.Output() != SUCCESS)
		RETURNFAIL("failed to output!");

	return SUCCESS;
}
