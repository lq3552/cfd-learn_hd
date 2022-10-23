/* Evolve Euler equations with Godunov Upwind Scheme
   written by: Qi Li
   Version: 1.0
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Nov 27, 2016 */

#include "Global.h"
using namespace Types;
#include "EOS.h"
#include "RiemannSolver.h"

Grid::GodunovSolverFirstOrder::GodunovSolverFirstOrder(Grid &grid) : Grid::GodunovSolver(grid)
{
}

int Grid::GodunovSolverFirstOrder::EvolveGodunov()
{
	/* First-order Godunov Solver, currently only 1st order, 1 D*/
	if (EOS(grid, p ,cs) != SUCCESS)
		RETURNFAIL("unable to calculate p and cs from d and e!\n");
	for (int i = 0; i < Global::StopCycle; i++)
	{
		/* Set boundary conditions */
		if (grid.SetBoundary(p, cs, U) != SUCCESS)
			RETURNFAIL("failed to apply boundary condition!\n");
		/* CFL-based condition */
		if (grid.HydroTimeStep(dx, time, cs, dt) != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		time += dt;
		printf("cycle = %d, dt = %f, t = %f\n", i+1, dt, time);
		/* compute interface numerical fluxes */
		if (ComputeFlux() != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		if (UpdateState() != SUCCESS)
			RETURNFAIL("failed to update state!\n");
		if (EOS(grid, p ,cs) != SUCCESS)
			RETURNFAIL("unable to calculate p and cs from d and e!\n");
		if (fabs(time - Global::StopTime) < TINY)
			break;
	}

	printf("Computation complete!\n");
	return SUCCESS;
}

int Grid::GodunovSolverFirstOrder::ComputeFlux()
{
	double* const WL(new double[3]); 
	double* const WR(new double[3]);
	double* const WS(new double[3]);// W = [d,u,p]
	double dS, uS, pS, eS, ES, cS, cL, cR;

	for (int i = 0; i < grid.GridDimension[0] + 2 * grid.NumberofGhostZones - 1; i ++)
	{
		WL[0] = d[i];
		WL[1] = u[i];
		WL[2] = p[i];
		cL = cs[i];
		WR[0] = d[i + 1];
		WR[1] = u[i + 1];
		WR[2] = p[i + 1];
		cR = cs[i + 1];
		if (Global::RiemannSolver == RiemannType::EXACT)
		{
			if (RiemannSolver(WL, cL, WR, cR, WS).RiemannExact() != SUCCESS)
				RETURNFAIL("failed to compute flux via Remann Solver!\n");
		}
		else
		{
			RETURNFAIL("unsupported Riemann Solver\n");
		}
		/* convert state to flux */
		dS = WS[0];
		uS = WS[1];
		pS = WS[2];
		pEOS(dS, pS, eS, cS);
		ES = eS + 0.5 * dS * uS * uS;
		F[0][i] = dS * uS;
		F[1][i] = dS * uS * uS + pS;
		F[2][i] = uS * (ES + pS);
	}
	delete[] WL;
	delete[] WR;
	delete[] WS;
	return SUCCESS;
}
