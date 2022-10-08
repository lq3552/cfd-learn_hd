#include "Global.h"
#include "RiemannSolver.h"

RiemannSolver::RiemannSolver(const double* const WL, const double cL,
		const double* const WR, const double cR, double* const WS) :
	dL(WL[0]),
	uL(WL[1]),
	pL(WL[2]),
	cL(cL),
	dR(WR[0]),
	uR(WR[1]),
	pR(WR[2]),
	cR(cR),
	WS(WS)
{
	G[0] = (Global::Gamma - 1.0) / (2.0 * Global::Gamma);
	G[1] = (Global::Gamma + 1.0) / (2.0 * Global::Gamma);
	G[2] = 2.0 * Global::Gamma / (Global::Gamma - 1.0);
	G[3] = 2.0 / (Global::Gamma - 1.0);
	G[4] = 2.0 / (Global::Gamma + 1.0);
	G[5] = (Global::Gamma - 1.0) / (Global::Gamma + 1.0);
	G[6] = (Global::Gamma - 1.0) / 2.0;
	G[7] = Global::Gamma - 1.0;
}

int RiemannSolver::RiemannExact()
{
	// compute star-region state
	if (StarRegion() != SUCCESS)
		RETURNFAIL("failed to compute state of star regions!\n");	
	if (Sampler() != SUCCESS)
		RETURNFAIL("failed to sample the solution!\n");
	return SUCCESS;
}


int RiemannSolver::StarRegion()
{
	// Purpose: solve pressure and velocity in star region
	double uS, pS;
	double change;
	double fR, dfR, fL, dfL, du;
	double p0, pold; // p0: initial guessed pressure

	// guess initial pressure for Newton Iteration
	if (GuessPressure(p0) != SUCCESS)
		RETURNFAIL("failed to guess initial pressure\n");
	pold = p0;
	du = uR - uL;
	// Iterate to solve f = fR + fL + du = 0  for p_star
	for (int i = 0; i < Global::RiemannIteration; i++)
	{
		if (PreFunc(fL, dfL, pold, dL, pL, cL) != SUCCESS)
			RETURNFAIL("failed to calculate fL of exact RS\n");
		if (PreFunc(fR, dfR, pold, dR, pR, cR) != SUCCESS)
			RETURNFAIL("Failed to calculate fR of exact RS\n");
		pS = pold - (fL + fR + du) / (dfL + dfR);
		change = 2.0 * fabs((pS - pold) / (pS + pold));
		if (change < TOL)
			break;
		if (pS < 0)
			pS = TOL;
		pold = pS;
	}
	if (change >= TOL)
		printf("WARNING: Divergence in Newton Iteration!\n");
	// compute velocity in star region
	uS = 0.5 * (uL + uR +fR -fL);
	
	WS[0] = 0.0; //do not solve rho for now
	WS[1] = uS;
	WS[2] = pS;
	return SUCCESS;
}

int RiemannSolver::GuessPressure(double &p0)
{
	/* Purpose: to provide a guess value for pressure pS in the star region.
	The choice is made according to adaptive Riemann solver
	using the PVRS, TRRS and TSRS approxiamet Riemann solvers. */
	double CUP, GEL, GER, uS, pmax, pmin, pPV, pQ, pTL, pTR, Qmax, Quser;
	Quser = 2.0;
	// Compute guess pressure from PVRS
	CUP = 0.25 * (dL + dR) * (cL + cR);
	pPV = 0.5 * (pL + pR) + 0.5 * (uL - uR) *CUP;
	pPV = fmax(0.0, pPV);
	pmin = fmin(pL, pR);
	pmax = fmax(pL, pR);
	Qmax = pmax / pmin;
	if (Qmax <= Quser && (pmin <= pPV && pPV <= pmax))
	{
		// select PVRS Riemann Solver
		p0 = pPV;
	}
	else
	{
		if(pPV < pmin)
		{
			// select two-rarefaction Riemann solver
			pQ = pow(pL / pR, G[0]);
			uS = (pQ * uL / cL + uR / cR + G[3] * (pQ - 1.0)) / (pQ / cL + 1.0 / cR);
			pTL = 1.0 + G[6] * (uL - uS) / cL;
			pTR = 1.0 + G[6] * (uS - uR) / cR;
			p0 = 0.5 * (pL * pow(pTL, G[2]) + pR * pow(pTR, G[2]));
		}
		else
		{
			// select two-shock Riemann solver with PVRS as estimate
			GEL = sqrt((G[4] / dL)/(G[5] * pL + pPV));
			GER = sqrt((G[4] / dR)/(G[5] * pR + pPV));
			p0 = (GEL * pL + GER * pR - (uR - uL)) / (GEL + GER);
		}
	}
	return SUCCESS;
}

int RiemannSolver::PreFunc(double &fK, double &dfK, const double p,
		const double dK, const double pK, const double cK)
{
	// purpose: to evalute the pressure functions fL and fR in exact Riemann solver
	double AK, BK, prat, qrt;
	if (p <= pK)
	{ // Rarefaction wave
		prat = p / pK;
		fK = G[3] * cK * (pow(prat, G[0]) - 1.0);
		dfK = (1.0 / (dK * cK)) * pow(prat, -G[1]);
	}
	else
	{ // Shock wave
		AK = G[4] / dK;
		BK = G[5] * pK;
		qrt = sqrt(AK / (BK+p));
		fK = (p - pK) * qrt;
		dfK = (1.0 - 0.5 * (p - pK) / (BK + p)) * qrt;
	}
	return SUCCESS;
}

int RiemannSolver::Sampler()
{
	/* purpose: to sample the solution throughout the wave pattern. Pressure pS and velocity uS in the Star Region are known.
	Sampling is performed in terms of the ’speed’ S = x/t = 0.
	Sampled values are density, velocity and pressure.
	Denote S firstly refers to star region but finally refers to "solution".*/
	double uS, pS, cS;
	double SHL, STL, SHR, STR, SL, SR;
	double C, pSL, pSR;
	uS = WS[1];
	pS = WS[2];
	// sampling
	if (0.0 <= uS)
	{
		// Supcase 1: Left wave
		if (pS > pL)
		{
			// Case 1: Left shock
			pSL = pS / pL;
			SL = uL - cL * sqrt(G[1] * pSL + G[0]);
			if (0.0 <= SL)
			{
				// subcase 1: sampled point is left data state
				WS[0] = dL;
				WS[1] = uL;
				WS[2] = pL;
			}
			else
			{
				// subcase 2: sampled point is star left state
				WS[0] = dL * (pSL + G[5]) / (pSL * G[5] + 1.0);
				WS[1] = uS;
				WS[2] = pS;
			}
		}
		else{
			// Case 2: Left rarefaction
			SHL = uL - cL;
			if (0.0 <= SHL)
			{
				// subcase 1: sampled point is left data state
				WS[0] = dL;
				WS[1] = uL;
				WS[2] = pL;
			}
			else
			{
				cS = cL * pow(pS / pL,G[0]);
				STL = uS - cS;
				if (0.0 > STL)
				{
					// subcase 2: sampled point is star left state
					WS[0] = dL*pow(pS / pL, 1.0 / Global::Gamma);
					WS[1] = uS;
					WS[2] = pS;
				}
				else
				{
					// subcase 3: sampled point is inside left fan
					WS[1] = G[4] * (cL + G[6] *uL);
					C = G[4] * (cL + G[6] * uL);
					WS[0] = dL * pow(C / cL,G[3]);
					WS[2] = pL * pow(C / cL,G[2]);
				}
			}
		}
	}
	else
	{
		// Supcase 2: Right wave
		if (pS > pR)
		{
			// Case 1: Right shock
			pSR = pS/pR;
			SR = uR + cR*sqrt(G[1]*pSR + G[0]);
			if (0.0 >= SR)
			{
				// subcase 1: sampled point is right data state
				WS[0] = dR;
				WS[1] = uR;
				WS[2] = pR;
			}
			else
			{
				// subcase 2: sampled point is star right state
				WS[0] = dR * (pSR + G[5]) / (pSR * G[5] + 1.0);
				WS[1] = uS;
				WS[2] = pS;
			}
		}
		else
		{
			// Case 2: Right rarefaction
			SHR = uR + cR;
			if (0.0 >= SHR)
			{
				// subcase 1: sampled point is right data state
				WS[0] = dR;
				WS[1] = uR;
				WS[2] = pR;
			}
			else
			{
				cS = cR * pow(pS / pR, G[0]);
				STR = uS + cS;
				if (0.0 <= STR)
				{
					// subcase 2: sampled point is star right state
					WS[0] = dR * pow(pS / pR, 1.0 / Global::Gamma);
					WS[1] = uS;
					WS[2] = pS;
				}
				else
				{
					// subcase 3: sampled point is inside right fan
					WS[1] = G[4] * (-cR + G[6] * uR);
					C = G[4] * (cR - G[6] * uR);
					WS[0] = dR * pow(C / cR,G[3]);
					WS[2] = pR * pow(C / cR,G[2]);
				}
			}
		}
	}

	return SUCCESS;
}
