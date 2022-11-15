/* Implement class methods that can be inherited by 
   Godunov solvers with different orders
   written by: Qi Li
   Version: 1.0
   create date: Nov 27, 2016 */

#include "Global.h"
using namespace Types;
#include "EOS.h"
#include "RiemannSolver.h"

Grid::GodunovSolver::GodunovSolver(Grid &grid) : grid(grid) 
{
	time = 0.0;
	dx = Global::LengthUnit / grid.GridDimension[0];

	/* alias */
	d = grid.GridData[DensNum];
	E = grid.GridData[TENum];
	e = grid.GridData[GENum];
	u = grid.GridData[Vel1Num];

	int size = 1;
	for (int i = 0; i < grid.GridRank; i++)
		size *= grid.GridDimension[i] + 2 * grid.NumberofGhostZones;
	p = new double[size];
	cs = new double[size];
	U = new double*[grid.GridRank * 3]; //Note: GridRank *3 only valid for 1D... will improve later
	F = new double*[grid.GridRank * 3];

	for (int i = 0; i < grid.GridRank * 3; i++)
	{
		U[i] = new double[size];
		F[i] = new double[size];
	}
	for (int i = grid.NumberofGhostZones; i < grid.GridDimension[0] +  grid.NumberofGhostZones; i++)
	{
		U[0][i] = d[i];
		U[1][i] = d[i] * u[i];
		U[2][i] = E[i];
		F[0][i] = 0.0;
		F[1][i] = 0.0;
		F[2][i] = 0.0;
	}

	std::cout << "Memory allocated for Godunov solver!" << std::endl;
}

Grid::GodunovSolver::~GodunovSolver()
{
	/* garbage collection */
	delete[] p;
	delete[] cs;
	for (int i = 0; i < grid.GridRank * 3; i++)
	{
		delete[] U[i];
		delete[] F[i];
	}
	delete[] U;
	delete[] F;

	std::cout << "Memory allocated via Godunov solver is cleaned up!" << std::endl;
}

int Grid::GodunovSolver::EvolveGodunov()
{
	/* First-order Godunov Solver, currently only 1st order, 1 D*/
	if (gEOS(grid, p ,cs) != SUCCESS)
		RETURNFAIL("unable to calculate p and cs from d and e!");
	for (int i = 0; i < Global::StopCycle; i++)
	{
		/* Set boundary conditions */
		if (grid.SetBoundary(p, cs, U) != SUCCESS)
			RETURNFAIL("failed to apply boundary condition!");
		/* CFL-based condition */
		if (grid.HydroTimeStep(dx, time, cs, dt) != SUCCESS)
			RETURNFAIL("failed to compute time step!");
		time += dt;
		std::cout << "cycle = " << (i + 1) << " dt = " << dt << " t = " << time << std::endl;
		/* compute interface numerical fluxes */
		if (ComputeFlux() != SUCCESS)
			RETURNFAIL("failed to compute time step!");
		if (UpdateState() != SUCCESS)
			RETURNFAIL("failed to update state!");
		if (gEOS(grid, p ,cs) != SUCCESS)
			RETURNFAIL("unable to calculate p and cs from d and e!");
		if (fabs(time - Global::StopTime) < TINY)
			break;
	}

	std::cout << "Computation complete!" << std::endl;
	return SUCCESS;
}

int Grid::GodunovSolver::ComputeFlux()
{
	double* const WL(new double[3]); 
	double* const WR(new double[3]);
	double* const WS(new double[3]);// W = [d,u,p]
	double dS, uS, pS, eS, ES, cS, cL, cR;

	for (int i = grid.NumberofGhostZones - 1; i < grid.GridDimension[0] + grid.NumberofGhostZones; i ++)
	{
		ReconstructInterface(i    , WL, cL,  1);
		ReconstructInterface(i + 1, WR, cR, -1);
		if (Global::RiemannSolver == RiemannType::EXACT)
		{
			if (RiemannSolver(WL, cL, WR, cR, WS).RiemannExact() != SUCCESS)
				RETURNFAIL("failed to compute flux via Remann Solver!");
		}
		else
		{
			RETURNFAIL("unsupported Riemann Solver");
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

int Grid::GodunovSolver::UpdateState()
{
	double dtodx = dt / dx;
	for (int i = grid.NumberofGhostZones; i < grid.GridDimension[0] + grid.NumberofGhostZones; i++)
	{
		for (int n = 0; n < grid.GridRank * 3; n++)
			U[n][i] = U[n][i] + dtodx * (F[n][i-1] - F[n][i]);
		d[i] = U[0][i];
		u[i] = U[1][i] / d[i];
		E[i] = U[2][i];
		e[i] = E[i] - 0.5 * d[i] * u[i] * u[i];
	}
	return SUCCESS;
}
