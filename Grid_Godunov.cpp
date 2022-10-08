/* Evolve Euler equations with Godunov Upwind Scheme
   written by: Qi Li
   Version: 1.0
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Nov 27, 2016 */

#include "Global.h"
#include "proto.h"
#include "EOS.h"

int Grid::GodunovSolver()
{
	/* Godunov Solver, currently only 1st order, 1 D*/
	/* TODO: use more storage-efficient data structure, i.e. use array alias and in-place operation */
	int size = 1;
	double time = 0.0, dt, dx = Global::LengthUnit / GridDimension[0];
	double *d, *E, *e, *u, *p, *cs;
	double **U, **F;
	for (int i = 0; i < GridRank; i++)
		size *= GridDimension[i] + 2 * NumberofGhostZones;
	d = GridData[DensNum];
	E = GridData[TENum];
	e = GridData[GENum];
	u = GridData[Vel1Num];
	p = new double[size];
	cs = new double[size];
	U = new double*[GridRank * 3]; //Note: GridRank *3 only valid for 1D... will improve later
	F = new double*[GridRank * 3];
	for (int i = 0; i < GridRank * 3; i++)
	{
		U[i] = new double[size];
		F[i] = new double[size];
	}
	for (int i = NumberofGhostZones; i < GridDimension[0] +  NumberofGhostZones; i++)
	{
		U[0][i] = d[i];
		U[1][i] = d[i] * u[i];
		U[2][i] = E[i];
		F[0][i] = 0.0;
		F[1][i] = 0.0;
		F[2][i] = 0.0;
	}
	if (EOS(*this, p ,cs) != SUCCESS)
		RETURNFAIL("unable to calculate p and cs from d and e!\n");
	for (int i = 0; i < Global::StopCycle; i++)
	{
		/* Set boundary conditions */
		if (SetBoundary(p, cs, U) != SUCCESS)
			RETURNFAIL("failed to apply boundary condition!\n");
		/* CFL-based condition */
		if (Hydro_TimeStep(dx, time, cs, dt) != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		time += dt;
		printf("cycle = %d, dt = %f, t = %f\n",i+1,dt,time);
		/* compute intercell numerical flux */
		if (Flux(d,E,e,u,p,cs,U,F,GridRank,GridDimension,NumberofGhostZones) != SUCCESS)
			RETURNFAIL("failed to compute time step!\n");
		if (Hydro_Update(dx,dt,d,E,e,u,p,cs,U,F,GridRank,GridDimension,NumberofGhostZones) != SUCCESS)
			RETURNFAIL("failed to update state!\n");
		if (EOS(*this, p ,cs) != SUCCESS)
			RETURNFAIL("unable to calculate p and cs from d and e!\n");
		if (fabs(time - Global::StopTime) < TINY)
			break;
	}

	/*
	for (i = 0; i < size; i++){
		Grid[DensNum][i] = d[i];
		Grid[TENum][i] = E[i];
		Grid[GENum][i] = e[i];
		Grid[Vel1Num][i] = u[i];
	}
	*/

	/* clean up */
	delete[] p;
	delete[] cs;
	delete[] U;
	delete[] F;
	printf("Computation complete!\n");
	return SUCCESS;
}

int Flux(double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,int GridRank,int* GridDimension,int NumberofGhostZones){
	int size = GridDimension[0] + 2 * NumberofGhostZones - 1;
	double *WL, *WR, *WS;// W = [d,u,p]
	double dS, uS, pS, eS, ES, cS, cL, cR;
	WL = new double[3];
	WR = new double[3];
	WS = new double[3];
	for (int i = 0; i < size; i ++)
	{
		WL[0] = d[i];
		WL[1] = u[i];
		WL[2] = p[i];
		cL = cs[i];
		WR[0] = d[i + 1];
		WR[1] = u[i + 1];
		WR[2] = p[i + 1];
		cR = cs[i + 1];
		if (Riemann(WL, cL, WR, cR, WS) != SUCCESS)
			RETURNFAIL("failed to compute flux via Remann Solver!\n");
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

int Hydro_Update(double dx, double dt, double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,int GridRank,int* GridDimension,int NumberofGhostZones)
{
	double dtodx = dt / dx;
	for (int i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++)
	{
		for (int n = 0; n < GridRank * 3; n++)
			U[n][i] = U[n][i] + dtodx * (F[n][i-1] - F[n][i]);
		d[i] = U[0][i];
		u[i] = U[1][i] / d[i];
		E[i] = U[2][i];
		e[i] = E[i] - 0.5 * d[i] * u[i] * u[i];
	}
	return SUCCESS;
}
