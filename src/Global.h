#ifndef GLOBAL_H
#define GLOBAL_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <exception>

#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define TOL 1e-6
#define MAX_DIMENSION 3
#define RETURNFAIL(x) {std::cerr << "ERROR: " << x << std::endl; return FAIL;}

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
		static void SetGlobalParameter(const int i_ProblemType,
				                 const double i_LengthUnit, const double i_TimeUnit, const double i_DensityUnit,
								 const Types::HydroType i_Solver, const Types::RiemannType i_RiemannSolver, const int i_RiemannIteration, const Types::BoundaryType i_BoundaryCondition,
								 const int i_EOSType, const float i_Gamma, const float i_Mu,
								 const float i_CourantNumber, const double i_StopTime, const int i_StopCycle);

	friend int SetParameter(Grid &grid, std::fstream& parameterFile);
};

#endif
