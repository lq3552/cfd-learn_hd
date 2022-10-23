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
	std::cout << "/* Problem paprameters */" << std::endl
			  << "ProblemType: " << ProblemType << std::endl

			  << "/* Units [cgs] */" << std::endl
			  << "LengthUnit: " << LengthUnit << std::endl
			  << "TimeUnit: " << TimeUnit << std::endl
			  << "DensityUnit: " << DensityUnit << std::endl

			  << "/* Hydrodynamics parameter */" << std::endl
			  << "Solver: " << static_cast<int>((Types::HydroType)Solver) << std::endl // use a map and operator overloading??
			  << "RiemannSolver: " << static_cast<int>((Types::RiemannType)RiemannSolver) << std::endl
			  << "RiemannIteration: " << RiemannIteration << std::endl
			  << "BoundaryCondition: " << static_cast<int>((Types::BoundaryType)BoundaryCondition) << std::endl

			  << "/* Thermal dynamics parameter */" << std::endl
			  << "EOSType: " << EOSType << std::endl
			  << "Gamma: " << Gamma << std::endl
			  << "Mu: " << Mu << std::endl

			  << "/* Time step */" << std::endl
			  << "CourantNumber: " << CourantNumber << std::endl
			  << "StopTime: " << StopTime << std::endl
			  << "StopCycle: " << StopCycle << std::endl;
}
