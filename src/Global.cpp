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
	std::cout << "/* Problem paprameters */\n"
			  << "ProblemType: " << ProblemType << "\n"

			  << "/* Units [cgs] */\n"
			  << "LengthUnit: " << LengthUnit << "\n"
			  << "TimeUnit: " << TimeUnit << "\n"
			  << "DensityUnit: " << DensityUnit << "\n"

			  << "/* Hydrodynamics parameter */\n"
			  //<< "Solver: " << Solver << "\n" // ERROR: use a template
			  //printf("RiemannSolver: %d\n", (int)RiemannSolver);
			  << "RiemannIteration: " << RiemannIteration << "\n"
			  //printf("BoundaryCondition: %d\n", (int)BoundaryCondition);

			  << "/* Thermal dynamics parameter */\n"
			  << "EOSType: " << EOSType << "\n"
			  << "Gamma: " << Gamma << "\n"
			  << "Mu: " << Mu << "\n"

			  << "/* Time step */\n"
			  << "CourantNumber: " << CourantNumber << "\n"
			  << "StopTime: " << StopTime << "\n"
			  << "StopCycle: " << StopCycle << std::endl;
}
