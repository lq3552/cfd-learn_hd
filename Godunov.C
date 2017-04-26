/* Evolve Euler equations with Godunov Upwind Scheme
   written by: Qi Li
   Version: 1.0
	         -- pure-hydro, 1-D, unigrid
	         -- in conjunction with exact riemman solver
   create date: Nov 27, 2016 */

#include <stdio.h>
#include <math.h>
#include "global.h"
#include "EOS.h"


int Boundary(double *d, double *E, double *e, double *u, double *p, double *cs, double **U);
int TimeStep(double dx, double time, double *u, double *cs, double &dt);
int Flux(double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F);
int Update(double dx, double dt, double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F);
int Riemann(double *WL, double cL, double *WR, double cR, double *WS);
int Output();

int GodunovSolver(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double time = 0.0,dt,dx = LengthUnit/GridDimension;
	double *d,*E,*e,*u,*p,*cs;
	double **U,**F;
	d = new double[size];
	E = new double[size];
	e = new double[size];
	u = new double[size];
	p = new double[size];
	cs = new double[size];
	U = new double*[GridRank*3];
	F = new double*[GridRank*3];
	for (i = 0; i < GridRank*3; i++){
		U[i] = new double[size];
		F[i] = new double[size];
	}
	for (i = NumberofGhostZones; i < GridDimension +  NumberofGhostZones; i++){
		d[i] = Grid[DensNum][i];
		E[i] = Grid[TENum][i];
		e[i] = Grid[GENum][i];
		u[i] = Grid[Vel1Num][i];
		U[0][i] = d[i];
		U[1][i] = d[i]*u[i];
		U[2][i] = E[i];
		F[0][i] = 0.0;
		F[1][i] = 0.0;
		F[2][i] = 0.0;
	}
	if (EOS(d,e,p,cs) != SUCCESS)
		RETURNFAIL("Unable to calculate p and cs from d and e!\n");
	for (i = 0; i < StopCycle; i++){
		// Set boundary conditions
		if (Boundary(d,E,e,u,p,cs,U) != SUCCESS)
			RETURNFAIL("Failed to apply boundary condition!\n");
		// CFL-based condition
		if (TimeStep(dx,time,u,cs,dt) != SUCCESS)
			RETURNFAIL("Failed to compute time step!\n");
		time += dt;
		printf("cycle = %d, dt = %f, t = %f\n",i+1,dt,time);
		// compute intercell numerical flux
		if (Flux(d,E,e,u,p,cs,U,F) != SUCCESS)
			RETURNFAIL("Failed to compute time step!\n");
		if (Update(dx,dt,d,E,e,u,p,cs,U,F) != SUCCESS)
			RETURNFAIL("Failed to update state!\n");
		if (EOS(d,e,p,cs) != SUCCESS)
			RETURNFAIL("Unable to calculate p and cs from d and e!\n");
		if (fabs(time - StopTime) < TINY) break;
	}
	for (i = 0; i < size; i++){
		Grid[DensNum][i] = d[i];
		Grid[TENum][i] = E[i];
		Grid[GENum][i] = e[i];
		Grid[Vel1Num][i] = u[i];
	}
	// clean up
	delete[] d;
	delete[] E;
	delete[] e;
	delete[] u;
	delete[] p;
	delete[] cs;
	delete[] U;
	delete[] F;
	printf("Computation complete!\n");
	return SUCCESS;
}
int Boundary(double *d, double *E, double *e, double *u, double *p, double *cs, double **U){
	/* Purpose: set boundary conditions
	   1 - outflow
	   2 - reflect (currently not supported)
	*/
	int i,j,k,n,rear = GridDimension + NumberofGhostZones -1;
	if (BoundaryCondition == 1){//outflow
		for (i = 0; i < NumberofGhostZones; i++){
			d[i] = d[NumberofGhostZones];
			E[i] = E[NumberofGhostZones];
			e[i] = e[NumberofGhostZones];
			u[i] = u[NumberofGhostZones];
			p[i] = p[NumberofGhostZones];
			cs[i] = cs[NumberofGhostZones];
			for (n = 0; n < GridRank*3; n++)
				U[n][i] = U[n][NumberofGhostZones];
		}
		for (i = GridDimension + NumberofGhostZones; i < GridDimension + 2*NumberofGhostZones; i++){
			d[i] = d[rear];
			E[i] = E[rear];
			e[i] = e[rear];
			u[i] = u[rear];
			p[i] = p[rear];
			cs[i] = cs[rear];
			for (n = 0; n < GridRank*3; n++)
				U[n][i] = U[n][rear];
		}
	}
	else
		RETURNFAIL("Unsupported boundary condition type!\n");
	return SUCCESS;
}

int TimeStep(double dx, double time, double *u, double *cs, double &dt){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double Smax = TINY;
	for (i = 0; i < size; i++)
		Smax = fmax(Smax,fabs(u[i]) + cs[i]);
	dt = CourantNumber*dx/Smax;
	if (time + dt > StopTime)
		dt = StopTime - time;
	return SUCCESS;
}

int Flux(double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F){
	int i,j,k,size = GridDimension + 2*NumberofGhostZones - 1;
	double *WL,*WR,*WS,*UL,*UR;// W = [d,u,p]
	double dS,uS,pS,eS,ES,cS,cL,cR;
	WL = new double[3];
	WR = new double[3];
	WS = new double[3];
	for (i = 0; i < size; i ++){
		WL[0] = d[i];
		WL[1] = u[i];
		WL[2] = p[i];
		cL = cs[i];
		WR[0] = d[i+1];
		WR[1] = u[i+1];
		WR[2] = p[i+1];
		cR = cs[i+1];
		if (Riemann(WL,cL,WR,cR,WS) != SUCCESS)
			RETURNFAIL("Failed to compute flux via Remann Solver!\n");
		// convert state to flux
		dS = WS[0];
		uS = WS[1];
		pS = WS[2];
		pEOS(dS,pS,eS,cS);
		ES = eS + 0.5*dS*uS*uS;
		F[0][i] = dS*uS;
		F[1][i] = dS*uS*uS + pS;
		F[2][i] = uS*(ES + pS);
	}
	delete[] WL;
	delete[] WR;
	delete[] WS;
	return SUCCESS;
}

int Update(double dx, double dt, double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F){
	int i,j,k,n;
	double dtodx = dt/dx;
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		for (n = 0; n < GridRank*3; n++)
			U[n][i] = U[n][i] + dtodx*(F[n][i-1] - F[n][i]);
		d[i] = U[0][i];
		u[i] = U[1][i]/d[i];
		E[i] = U[2][i];
		e[i] = E[i] - 0.5*d[i]*u[i]*u[i];
	}
	return SUCCESS;
}
