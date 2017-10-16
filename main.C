/* Main function, control the root level problem solution process
   Author : Qi Li (pg3552@ufl.edu)
   create : Nov. 27, 2016 
   Update1: Oct. 16, 2017
 */

#include <stdio.h>
#include "global.h"
#include "grid.h"

int SetParameter(FILE *fptr);
int InitializeNew();

grid Grid;

int main(int argc, char *argv[]){
	FILE *fptr;
	if (argc > 1){
		printf("Reading parameter file to set global parameters...\n");
		if ((fptr = fopen(argv[1],"r")) == NULL)
			RETURNFAIL("ERROR: failed to open parameter file!\n");
		if (SetParameter(fptr) != SUCCESS)
			RETURNFAIL("ERROR: failed to set global parameters from file!\n");
		printf("Setting parameters successes!\n");
	}
	printf("%f\n",LengthUnit);
	Grid.PrintMetaData();
	if (InitializeNew() != SUCCESS)
		RETURNFAIL("ERROR: failed to initialize problem!\n");
	if (Solver == 1){
		if (Grid.GodunovSolver() != SUCCESS)
			RETURNFAIL("ERROR: failure in Godunov solver!\n");
	}
	if (Grid.Output() != SUCCESS)
		RETURNFAIL("ERROR: failed to output!\n");
	return SUCCESS;
}
