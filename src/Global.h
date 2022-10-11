#ifndef GLOBAL_H
#define GLOBAL_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <exception>
using namespace std;

#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define TOL 1e-6
#define MAX_LINE_LENGTH 100
#define MAX_DIMENSION 3
#define RETURNFAIL(x) {printf("ERROR: %s",x);return FAIL;}

#include "Property.h"
#include "typedefs.h"
#include "Grid.h"

class Global
{
	public:
		/* Problem parameters  */
		static Property<int> ProblemType;

		/* Units [cgs] */
		static Property<double> LengthUnit; // inline since C++17
		static Property<double> TimeUnit;
		static Property<double> DensityUnit;

		/* Hydrodynamics parameter */
		static Property<int> Solver;
		static Property<int> RiemannSolver;
		static Property<int> RiemannIteration;
		static Property<int> BoundaryCondition;

		/* Thermal dynamics parameter */
		static Property<int> EOSType;
		static Property<float> Gamma;
		static Property<float> Mu;

		/* Time step */
		static Property<float> CourantNumber;
		static Property<double> StopTime;
		static Property<int> StopCycle;

		/* Output */
		static Property<char>* DataDump; //prefix of output
		static Property<double> dtDump; // cycle of output

		static void PrintGlobalParameter();

	private:
		static void SetGlobalParameter(int i_ProblemType,
				                 double i_LengthUnit, double i_TimeUnit, double i_DensityUnit,
								 int i_Solver, int i_RiemannSolver, int i_RiemannIteration, int i_BoundaryCondition,
								 int i_EOSType, float i_Gamma, float i_Mu,
								 float i_CourantNumber, double i_StopTime, int i_StopCycle);

	friend int SetParameter(Grid &grid, FILE *fptr);
};

#endif
