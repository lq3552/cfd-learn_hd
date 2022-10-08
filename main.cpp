/* Main function, control the root level problem solution process
   Author : Qi Li (pg3552@ufl.edu)
   create : Nov. 27, 2016 
   Update1: Oct. 16, 2017
 */

#include "Global.h"
#include "Grid.h"

int main(int argc, char *argv[])
{
	Grid grid;
	FILE *fptr;

	if (argc > 1)
	{
		printf("Reading parameter file to set global parameters...\n");
		if ((fptr = fopen(argv[1],"r")) == NULL)
			RETURNFAIL("failed to open parameter file!\n");
		if (SetParameter(grid, fptr) != SUCCESS)
			RETURNFAIL("failed to set global parameters from file!\n");
		printf("Setting parameters succeeds!\n");
	}
	else
	{
		RETURNFAIL("please provide the parameter file: (EXE) PATH_TO_PARAMETER_FILE\n");
	}

	if (Grid::GridInitializer(grid).TestInitialize(Global::ProblemType) != SUCCESS)
		RETURNFAIL("failed to initialize problem!\n");

	if (Global::Solver == HD)
	{
		if (Grid::GodunovSolver(grid).EvolveGodunovFirstOrder() != SUCCESS)
			RETURNFAIL("failure in Godunov solver!\n");
	}

	if (grid.Output() != SUCCESS)
		RETURNFAIL("failed to output!\n");

	return SUCCESS;
}
