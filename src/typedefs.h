/* Define customized types for number precisions, solvers and fields  */
// currently many are useless but reserved for future use

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef int FieldType;

namespace Types
{
	/* Baryon Field Index */
	const FieldType
		DensNum = 0,
		TENum = 1,
		GENum = 2,
		Vel1Num = 3,
		Vel2Num = 4,
		Vel3Num = 5;

	/* Boundary Condition */
	enum class BoundaryType
	{
		PERIODIC = 0,
		OUTFLOW = 1
	};

	/* Hydro Solver Framework */
	enum class HydroType
	{
		HD_1ST = 0,
		HD_2ND = 1,
		MHDCT = 2
	};

	/* Riemann Solver */
	enum class RiemannType
	{
		EXACT = 0,
		HLLC  = 1,
		HLLD  = 2
	};
}

#endif
