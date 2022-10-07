/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include <stdio.h>
#include "Global.h"
#include "typedefs.h"
#include "Grid.h"

/* Field Index */
int DensNum = 0;  
int TENum = 1; 
int GENum = 2; 
int Vel1Num = 3;

/* Problem parameters  */
int ProblemType = 5;

/* Units [cgs] */
double LengthUnit = 1;
double TimeUnit = 1;
double DensityUnit = 1;

/* Hydrodynamics parameter */
int Solver = HD;//1: Godunov 1st order
int RiemannSolver = Exact;
int RiemannIteration = 20;
int BoundaryCondition = Outflow; //1: outflow

/* Thermal dynamics parameter */
int EOSType = 1;
float Gamma = 1.4;
float Mu = 0.6;

/* Time step */
float CourantNumber = 0.4;
double StopTime = 0.25;
int StopCycle = 1000000;

/* Output */
char* DataDump;
double dtDump;

int SetParameter(Grid &grid, FILE* fptr)
{
	// future development: identify optional/compelling parameters, comment, dummy space
	char line[MAX_LINE_LENGTH];
	int ret = 1;
	int comment_count = 0;
	
	/* Default Top grid parameters*/
	int GridRank = 1;
	int GridDimension[MAX_DIMENSION] = {0};
	int NumberofGhostZones = 1;
	int NumberofBaryonFields = 4;

	rewind(fptr);
	while ((fgets(line, MAX_LINE_LENGTH,fptr) != NULL) && ret && (comment_count<2))
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
		ret += sscanf(line,"BoundaryCondition = %d",&BoundaryCondition);
		ret += sscanf(line,"EOSType = %d",&EOSType);
		ret += sscanf(line,"Gamma = %f",&Gamma);
		ret += sscanf(line,"Mu = %f",&Mu);
		ret += sscanf(line,"CourantNumber = %f",&CourantNumber);
		ret += sscanf(line,"StopTime = %lf",&StopTime);
		ret += sscanf(line,"StopCycle = %d",&StopCycle);
	}
	grid.SetMetaData(GridRank, GridDimension, NumberofGhostZones, NumberofBaryonFields);
	return SUCCESS;
}
