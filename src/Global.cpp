/* Implementation of Global class */

#include "Global.h"
using namespace Types;

/* static methods */
void Global::SetGlobalParameter(const int i_ProblemType,
		                  const double i_LengthUnit, const double i_TimeUnit, const double i_DensityUnit,
						  const HydroType i_Solver, const RiemannType i_RiemannSolver, const int i_RiemannIteration, const BoundaryType i_BoundaryCondition,
						  const int i_EOSType, const float i_Gamma, const float i_Mu,
						  const float i_CourantNumber, const double i_StopTime, const int i_StopCycle,
						  const std::string i_DataDump, const double i_dtDump)
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
	DataDump          = i_DataDump;
	dtDump            = i_dtDump;
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
	if (dtDump < 0 || dtDump > StopTime)
	{
		dtDump = i_StopTime;
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
