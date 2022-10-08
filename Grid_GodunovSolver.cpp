/* Evolve Euler equations with Godunov Upwind Scheme
   written by: Qi Li
   Version: 1.0
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Nov 27, 2016 */

#include "Global.h"
#include "proto.h"
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
}

int Grid::GodunovSolver::EvolveGodunovFirstOrder()
{
	/* First-order Godunov Solver, currently only 1st order, 1 D*/
	/* TODO: use more storage-efficient data structure, i.e. use array alias and in-place operation */

	if (EOS(grid, p ,cs) != SUCCESS)
		RETURNFAIL("unable to calculate p and cs from d and e!\n");
	for (int i = 0; i < Global::StopCycle; i++)
	{
		/* Set boundary conditions */
		if (grid.SetBoundary(p, cs, U) != SUCCESS)
			RETURNFAIL("failed to apply boundary condition!\n");
		/* CFL-based condition */
		if (grid.Hydro_TimeStep(dx, time, cs, dt) != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		time += dt;
		printf("cycle = %d, dt = %f, t = %f\n", i+1, dt, time);
		/* compute interface numerical fluxes */
		if (FluxFirstOrder() != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		if (Hydro_Update() != SUCCESS)
			RETURNFAIL("failed to update state!\n");
		if (EOS(grid, p ,cs) != SUCCESS)
			RETURNFAIL("unable to calculate p and cs from d and e!\n");
		if (fabs(time - Global::StopTime) < TINY)
			break;
	}

	printf("Computation complete!\n");
	return SUCCESS;
}

int Grid::GodunovSolver::FluxFirstOrder(){
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
		if (Global::RiemannSolver == Exact)
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

int Grid::GodunovSolver::Hydro_Update()
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
