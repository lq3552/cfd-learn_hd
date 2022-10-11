#ifndef GLOBAL_H
#define GLOBAL_H

#include <math.h>
#include <stdio.h>
#include <iostream> // TODO: remove the dependence on stdio.h
#include <exception>
using namespace std;

#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define TOL 1e-6
#define MAX_LINE_LENGTH 100
#define MAX_DIMENSION 3
#define RETURNFAIL(x) {printf("ERROR: %s",x);return FAIL;}

#include "typedefs.h"
#include "Grid.h"

class Global
{
	public:
		/* Problem parameters  */
		static int ProblemType;

		/* Units [cgs] */
		static double LengthUnit; // inline since C++17
		static double TimeUnit;
		static double DensityUnit;

		/* Hydrodynamics parameter */
		static int Solver;
		static int RiemannSolver;
		static int RiemannIteration;
		static int BoundaryCondition;

		/* Thermal dynamics parameter */
		static int EOSType;
		static float Gamma;
		static float Mu;

		/* Time step */
		static float CourantNumber;
		static double StopTime;
		static int StopCycle;

		/* Output */
		static char* DataDump; //prefix of output
		static double dtDump; // cycle of output

	private:
		static void SetGlobalParameter(int i_ProblemType,
				                 double i_LengthUnit, double i_TimeUnit, double i_DensityUnit,
								 int i_Solver, int i_RiemannSolver, int i_RiemannIteration, int i_BoundaryCondition,
								 int i_EOSType, float i_Gamma, float i_Mu,
								 float i_CourantNumber, double i_StopTime, int i_StopCycle);
		static void PrintGlobalParameter();

	friend int SetParameter(Grid &grid, FILE *fptr);
};

#endif
