#ifndef GLOBAL_H
#define GLOBAL_H

#include <math.h>
#include <stdio.h>
#include <iostream> // for next version
#include <exception>
using namespace std;

#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define RETURNFAIL(x) {printf("ERROR: %s",x);return FAIL;}
#define TOL 1e-6
#define MAX_LINE_LENGTH 100
#define MAX_DIMENSION 3

/* Problem parameters  */
extern int ProblemType;

/* Units [cgs] */
extern double LengthUnit,TimeUnit,DensityUnit;

/* Field Index */
// the current setup is dangerous, because it is possible to change those values somewhere except for initialization
extern int DensNum;  
extern int TENum; 
extern int GENum; 
extern int Vel1Num; 

/* Hydrodynamics parameter */
extern int Solver;
extern int RiemannSolver;
extern int RiemannIteration;
extern int BoundaryCondition;

/* Thermal dynamics parameter */
extern int EOSType;
extern float Gamma;
extern float Mu;

/* Time step */
extern float CourantNumber;
extern double StopTime;
extern int StopCycle;

/* Output */
extern char* DataDump; //prefix of output
extern double dtDump; // cycle of output

#endif
