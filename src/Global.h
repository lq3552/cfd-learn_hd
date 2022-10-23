#ifndef GLOBAL_H
#define GLOBAL_H

#include <math.h>
#include <stdio.h>
#include <iostream>
#include <exception>

#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define TOL 1e-6
#define MAX_LINE_LENGTH 100
#define MAX_DIMENSION 3
#define RETURNFAIL(x) {std::cout << "ERROR: " << (x) << std::endl; return FAIL;}

#include "Property.h"
#include "typedefs.h"
#include "Grid.h"

class Global
{
	public:
		/* Problem parameters  */
		inline static Property<int> ProblemType;

		/* Units [cgs] */
		inline static Property<double> LengthUnit; // inline since C++17
		inline static Property<double> TimeUnit;
		inline static Property<double> DensityUnit;

		/* Hydrodynamics parameter */
		inline static Property<Types::HydroType> Solver;
		inline static Property<Types::RiemannType> RiemannSolver;
		inline static Property<int> RiemannIteration;
		inline static Property<Types::BoundaryType> BoundaryCondition;

		/* Thermal dynamics parameter */
		inline static Property<int> EOSType;
		inline static Property<float> Gamma;
		inline static Property<float> Mu;

		/* Time step */
		inline static Property<float> CourantNumber;
		inline static Property<double> StopTime;
		inline static Property<int> StopCycle;

		/* Output */
		inline static Property<char>* DataDump; //prefix of output
		inline static Property<double> dtDump; // cycle of output

		static void PrintGlobalParameter();

	private:
		static void SetGlobalParameter(int i_ProblemType,
				                 double i_LengthUnit, double i_TimeUnit, double i_DensityUnit,
								 Types::HydroType i_Solver, Types::RiemannType i_RiemannSolver, int i_RiemannIteration, Types::BoundaryType i_BoundaryCondition,
								 int i_EOSType, float i_Gamma, float i_Mu,
								 float i_CourantNumber, double i_StopTime, int i_StopCycle);

	friend int SetParameter(Grid &grid, FILE *fptr);
};

#endif
