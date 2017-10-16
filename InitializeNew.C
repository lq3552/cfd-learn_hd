#include <stdio.h>
#include "global.h"
#include "grid.h"

// The relation between it and Grid is also a bit messy, try to improve it!
int InitializeNew(){
	int i,size=1;
	for (i = 0; i < Grid.GridRank; i++)
		size *= Grid.GridDimension[i] + 2*Grid.NumberofGhostZones;
	printf("Problem Type: %d\n",ProblemType);
	switch (ProblemType){
		case 1:
			if (Grid.Grid_Test1Initialize() != SUCCESS)
				return FAIL;
			break;
		case 2:
			if (Grid.Grid_Test2Initialize() != SUCCESS)
				return FAIL;
			break;
		case 3:
			if (Grid.Grid_Test3Initialize() != SUCCESS)
				return FAIL;
			break;
		case 4:
			if (Grid.Grid_Test4Initialize() != SUCCESS)
				return FAIL;
			break;
		case 5:
			if (Grid.Grid_Test5Initialize() != SUCCESS)
				return FAIL;
			break;
		default:
			RETURNFAIL("Unsupported ProblemType!\n");
	}
	return SUCCESS;
}
