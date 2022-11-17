/* Define the grid class which holds the computation domain and the relevant solver */

#ifndef GRID_H
#define GRID_H

class Grid
{
	private:
	/* Top grid parameters */
		int GridRank; 
		int GridDimension[MAX_DIMENSION];
		int NumberofGhostZones;
		int NumberofBaryonFields;
		double **GridData;
	
		int SetBoundary(double *p, double *cs, double **U);
		void SetGhostValue(int i, int i_bound, double *p, double *cs, double **U);
		void SetMetaData(const int i_GridRank, const int i_GridDimension[], const int i_NumberofGhostZones, const int i_NumberofBaryonFields);
	
	public:
		~Grid(); // free dynamically allocated space
		void PrintMetaData() const;
		int Output(int, std::string = ".txt") const;

		class GridInitializer;
		class GodunovSolver;
		class GodunovSolverFirstOrder;
		class GodunovSolverSecondOrder;
	
		friend int SetParameter(Grid &grid, std::fstream& parameterFile);
		friend int gEOS(Grid &grid, double *p,double *cs);
};

class Grid::GridInitializer
{
	private:
		Grid &grid; // reference to top grid

		void AssignPrimitive(double (&w)[4], double d, double u, double p);
		int AllocateGrid();

	public:
		GridInitializer(Grid &p_grid);
		int TestInitialize(int setNo);
};

class Grid::GodunovSolver // abstract class with at least one pure virtual method
{
	protected:
		Grid &grid; // reference to top grid
		double *d, *E, *e, *u; // alias of density, total energy, internal energy, velocity
		double *p, *cs; // pressure, sound speed
		double **U; // volume-centered conserved quantities
		double **F; // interface fluxes
		double time, dx, dt;
		double timeNextOutput;

		double SetTimeStep() const;
		int ComputeFlux();
		virtual void ReconstructInterface(int, double* const, double&, int) = 0;
		int UpdateState();

	public:
		GodunovSolver(Grid &p_grid);
		virtual ~GodunovSolver();
		int EvolveGodunov();
};

class Grid::GodunovSolverFirstOrder : public Grid::GodunovSolver
{
	protected:
		void ReconstructInterface(int i, double* const W, double &c, int);
	public:
		GodunovSolverFirstOrder(Grid &p_grid);
};

class Grid::GodunovSolverSecondOrder : public Grid::GodunovSolver
{
	protected:
		inline double VanLeer(int i, double *q);
		void ReconstructInterface(int i, double* const W, double &c, int = 1);
	public:
		GodunovSolverSecondOrder(Grid &p_grid);
};

#endif
