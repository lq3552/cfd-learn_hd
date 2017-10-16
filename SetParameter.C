/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include <stdio.h>
#include "global.h"
#include "grid.h"

/* global type declaration*/

/* Problem parameters  */
int ProblemType = 5;

/* Units [cgs] */
double LengthUnit = 1;
double TimeUnit = 1;
double DensityUnit = 1;

/* Field Index */
int DensNum = 0;  
int TENum = 1; 
int GENum = 2; 
int Vel1Num = 3;

/* Hydrodynamics parameter */
int Solver = 1;//1: Godunov 1st order
int RiemannIteration = 20;
int BoundaryCondition = 1; //1: outflow

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

int SetParameter(FILE* fptr){
	// future develop: identify optional/compelling parameters, comment, dummy space
	char line[MAX_LINE_LENGTH];
	int ret;
	int comment_count = 0;
	
	/* Default Top grid parameters*/
	int GridRank = 1;
	int GridDimension[MAX_DIMENSION] = {0};
	int NumberofGhostZones = 1;
	int NumberofBaryonFields = 4;

	rewind(fptr);
	while ((fgets(line, MAX_LINE_LENGTH,fptr) != NULL) && (comment_count<2)){
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
		ret += sscanf(line,"RiemannIteration = %d",&RiemannIteration);
		ret += sscanf(line,"BoundaryCondition = %d",&BoundaryCondition);
		ret += sscanf(line,"EOSType = %d",&EOSType);
		ret += sscanf(line,"Gamma = %f",&Gamma);
		ret += sscanf(line,"Mu = %f",&Mu);
		ret += sscanf(line,"CourantNumber = %f",&CourantNumber);
		ret += sscanf(line,"StopTime = %lf",&StopTime);
		ret += sscanf(line,"StopCycle = %d",&StopCycle);
	}
	Grid.SetMetaData(GridRank,GridDimension,NumberofGhostZones,NumberofBaryonFields);
	return SUCCESS;
}

void grid::SetMetaData(int m_GridRank,int m_GridDimension[MAX_DIMENSION],int m_NumberofGhostZones,int m_NumberofBaryonFields){
	int i;
	GridRank = m_GridRank;
	for (i = 0; i < GridRank; i++)
		GridDimension[i] = m_GridDimension[i];
	NumberofGhostZones = m_NumberofGhostZones;
	NumberofBaryonFields = m_NumberofBaryonFields;
}
