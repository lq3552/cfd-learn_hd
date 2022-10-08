/* Implementation of Global class */

#include "Global.h"

/* static members */
int    Global::ProblemType;
double Global::LengthUnit;
double Global::TimeUnit;
double Global::DensityUnit;
int    Global::Solver;
int    Global::RiemannSolver;
int    Global::RiemannIteration;
int    Global::BoundaryCondition;
int    Global::EOSType;
float  Global::Gamma;
float  Global::Mu;
float  Global::CourantNumber;
double Global::StopTime;
int    Global::StopCycle;
char* Global::DataDump;
double Global::dtDump;

/* static methods */
void Global::SetGlobalParameter(int i_ProblemType,
		                  double i_LengthUnit, double i_TimeUnit, double i_DensityUnit,
						  int i_Solver, int i_RiemannSolver, int i_RiemannIteration, int i_BoundaryCondition,
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
	StopTime          = i_StopTime;
	StopCycle         = i_StopCycle;
}

void Global::PrintGlobalParameter()
{
	printf("/* Problem paprameters */\n");
	printf("ProblemType: %d\n", ProblemType);

	printf("/* Units [cgs] */\n");
	printf("LengthUnit: %g\n", LengthUnit);
	printf("TimeUnit: %g\n", TimeUnit);
	printf("DensityUnit: %g\n", DensityUnit);

	printf("/* Hydrodynamics parameter */\n");
	printf("Solver: %d\n", Solver);
	printf("RiemannSolver: %d\n", RiemannSolver);
	printf("RiemannIteration: %d\n", RiemannIteration);
	printf("BoundaryCondition: %d\n", BoundaryCondition);

	printf("/* Thermal dynamics parameter */\n");
	printf("EOSType: %d\n", EOSType);
	printf("Gamma: %g\n", Gamma);
	printf("Mu: %g\n", Mu);

	printf("/* Time step */\n");
	printf("CourantNumber: %g\n", CourantNumber);
	printf("StopTime: %g\n", StopTime);
	printf("StopCycle: %d\n", StopCycle);
}
