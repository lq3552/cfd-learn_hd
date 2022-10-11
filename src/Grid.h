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
		int Hydro_TimeStep(double dx, double time, double *cs, double &dt);
		void SetMetaData(int i_GridRank, int i_GridDimension[], int i_NumberofGhostZones, int i_NumberofBaryonFields);
	
	public:
		~Grid(); // free dynamically allocated space
		void PrintMetaData();
		int Output();

		class GridInitializer;
		class GodunovSolver;
	
		friend int SetParameter(Grid &grid, FILE* fptr);
		friend int EOS(Grid &grid, double *p,double *cs);
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

class Grid::GodunovSolver
{
	private:
		Grid &grid; // reference to top grid
		double *d, *E, *e, *u; // alias of density, total energy, internal energy, velocity
		double *p, *cs; // pressure, sound speed
		double **U; // volume-centered conserved quantities
		double **F; // interface fluxes
		double time, dx, dt;

	public:
		GodunovSolver(Grid &p_grid);
		~GodunovSolver();
		int EvolveGodunovFirstOrder();
		int FluxFirstOrder();
		int Hydro_Update();
};

#endif
