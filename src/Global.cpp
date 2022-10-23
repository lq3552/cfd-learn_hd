/* Implementation of Global class */

#include "Global.h"
using namespace Types;

/* static methods */
void Global::SetGlobalParameter(int i_ProblemType,
		                  double i_LengthUnit, double i_TimeUnit, double i_DensityUnit,
						  HydroType i_Solver, RiemannType i_RiemannSolver, int i_RiemannIteration, BoundaryType i_BoundaryCondition,
						  int i_EOSType, float i_Gamma, float i_Mu,
						  float i_CourantNumber, double i_StopTime, int i_StopCycle)
{
	ProblemType       = i_ProblemType;
	LengthUnit        = i_LengthUnit;
	TimeUnit          = i_TimeUnit;
	DensityUnit       = i_DensityUnit;
	Solver            = i_Solver;
	RiemannSolver     = i_RiemannSolver;
	RiemannIteration  = i_RiemannIteration;
	BoundaryCondition = i_BoundaryCondition;
	EOSType           = i_EOSType;
	Gamma             = i_Gamma;
	Mu                = i_Mu;
	CourantNumber     = i_CourantNumber;
	StopCycle         = i_StopCycle;
	switch (i_ProblemType) // override StopTime from param file if a test problem is set
	{
		case 0:
			StopTime = 0.20;
			break;
		case 1:
			StopTime = 0.15;
			break;
		case 2:
			StopTime = 0.012;
			break;
		case 3:
			StopTime = 0.035;
			break;
		case 4:
			StopTime = 0.012;
			break;
		default:
			StopTime = i_StopTime;
			break;
	}
}

void Global::PrintGlobalParameter()
{
	printf("/* Problem paprameters */\n");
	printf("ProblemType: %d\n", (int)ProblemType);

	printf("/* Units [cgs] */\n");
	printf("LengthUnit: %g\n", (double)LengthUnit);
	printf("TimeUnit: %g\n", (double)TimeUnit);
	printf("DensityUnit: %g\n", (double)DensityUnit);

	printf("/* Hydrodynamics parameter */\n");
	//printf("Solver: %d\n", (int)Solver);
	//printf("RiemannSolver: %d\n", (int)RiemannSolver);
	printf("RiemannIteration: %d\n", (int)RiemannIteration);
	//printf("BoundaryCondition: %d\n", (int)BoundaryCondition);

	printf("/* Thermal dynamics parameter */\n");
	printf("EOSType: %d\n", (int)EOSType);
	printf("Gamma: %g\n", (float)Gamma);
	printf("Mu: %g\n", (float)Mu);

	printf("/* Time step */\n");
	printf("CourantNumber: %g\n", (float)CourantNumber);
	printf("StopTime: %g\n", (double)StopTime);
	printf("StopCycle: %d\n", (int)StopCycle);
}
