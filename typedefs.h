/* Define customized types for number precisions, solvers and fields  */
// currently many are useless but reserved for future use

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef int field_type;
typedef int boundary_type;
typedef int hydro_type;
typedef int riemann_type;

/* Baryon Field */
const field_type
	Density = 0,
	TotalEnergy = 1,
	InternalEnergy = 2,
	Velocity1 = 3,
	Velocity2 = 4,
	Velocity3 = 5;

/* Boundary Condition */
const boundary_type
	Periodic = 0,
	Outflow = 1;
	
/* Hydro Solver Framework */
const hydro_type
	HD = 0,
	MHDCT = 1;

/* Riemann Solver */
const riemann_type
	Exact = 0,
	HLLC  = 1,
	HLLD  = 2;

#endif
