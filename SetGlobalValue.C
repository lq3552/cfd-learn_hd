/* Read parameters from a file
   Written by: Qi Li
   create date : Nov. 30, 2016*/

#include <stdio.h>
#include "global.h"

/* global type declaration*/

/* Problem parameters  */
int ProblemType = 5;

/* Top grid parameters */
int GridRank = 1;
int GridDimension = 1000;
int NumberofGhostZones = 1;
double **Grid;

/* data field index */
int DensNum = 0;
int TENum = 1;
int GENum = 2;
int Vel1Num = 3;

/* Units [cgs] */
double LengthUnit = 1;
double TimeUnit = 1;
double DensityUnit = 1;

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

int SetGlobalValue(FILE* fptr){
	// future develop: identify optional/compelling parameters, comment, dummy space
	char line[MAX_LINE_LENGTH];
	int i,dim,ret,int_dummy;
	double TempFloat,float_dummy;
	int comment_count = 0;
	rewind(fptr);
	while ((fgets(line, MAX_LINE_LENGTH,fptr) != NULL) && (comment_count<2)){
		ret = 0;
		/* read parameters */
		ret += sscanf(line,"ProblemType = %d",&ProblemType);
		ret += sscanf(line,"GridRank = %d",&GridRank);
		ret += sscanf(line,"GridDimension = %d",&GridDimension);
		ret += sscanf(line,"NumberofGhostZones = %d",&NumberofGhostZones);
		ret += sscanf(line,"DensNum = %d",&DensNum);
		ret += sscanf(line,"TENum = %d",&TENum);
		ret += sscanf(line,"GENum = %d",&GENum);
		ret += sscanf(line,"Vel1Num = %d",&Vel1Num);
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
	return SUCCESS;
}
