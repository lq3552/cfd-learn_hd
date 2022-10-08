/* Local Riemann Solver
   created on Nov. 27, 2016
   refactored on Oct. 8, 2022
   written by Qi Li
   Purpose: solve Local Riemman Problem of Euler Equations
   Version:
   1.0: 1D, pure hydro, exact Riemann solver (Nov. 27, 2016)
*/

class RiemannSolver
{
	private:
		float G[8]; // Gamma related constants TODO: a better solution to make it static const
		const double dL, uL, pL, cL; // density, velocity, pressure, sound speed
		const double dR, uR, pR, cR;
		double* const WS; // star region primitives

		int StarRegion();
		int GuessPressure(double &p0);
		int PreFunc(double &fK, double &dfK, const double p,
				const double dK, const double pK, const double cK);
		int Sampler();

	public:
		RiemannSolver(const double* const WL, const double cL,
				const double* const WR, const double cR, double* const WS);
		int RiemannExact();
};
