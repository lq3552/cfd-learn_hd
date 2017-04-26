/* Main function, control the root level problem solution process
   create date: Nov. 27, 2016 */

#include <stdio.h>
#include <math.h>
#include "global.h"
#include "EOS.h"

int Grid_Initialize();
int GodunovSolver();
int Output();
int SetGlobalValue(FILE *fptr);

int main(int argc, char *argv[]){
	FILE *fptr;
	if (argc > 1){
		printf("Reading parameter file to set global parameters...\n");
		if ((fptr = fopen(argv[1],"r")) == NULL)
			RETURNFAIL("ERROR: failed to open parameter file!\n");
		if (SetGlobalValue(fptr) != SUCCESS)
			RETURNFAIL("ERROR: failed to set global parameters from file!\n");
		printf("Setting parameters successes!\n");
	}
	printf("%f\n",LengthUnit);
	printf("GridRank: %d\n",GridRank);
	printf("GridDimension: %d\n",GridDimension);
	if (Grid_Initialize() != SUCCESS)
		RETURNFAIL("ERROR: failed to initialize grid!\n");
	if (Solver == 1){
		if (GodunovSolver() != SUCCESS)
			RETURNFAIL("ERROR: failure in Godunov solver!\n");
	}
	if (Output() != SUCCESS)
		RETURNFAIL("ERROR: failed to output!\n");
	return SUCCESS;
}
