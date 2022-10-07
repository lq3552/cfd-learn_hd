/*Define the grid class which holds the computation domain and the relevant solver*/

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
		double **GridData; //TODO: use C++ standard container instead of C-flavor (though MPI could be not as straightforward)
	
		int SetBoundary(double *p, double *cs, double **U);
		int Hydro_TimeStep(double dx, double time, double *cs, double &dt);
		void SetMetaData(int m_GridRank, int m_GridDimension[], int m_NumberofGhostZones, int m_NumberofBaryonFields);
	
	public:
		void PrintMetaData();
		int Output();
		int GodunovSolver();
		//~Grid(); // free dynamically allocated space

		class GridInitializer;
	
		friend int SetParameter(Grid &grid, FILE* fptr);
		friend int EOS(Grid &grid, double *p,double *cs);
};

class Grid::GridInitializer
{
	private:
		Grid &grid; // reference to grid

		void AssignPrimitive(double (&w)[4], double d, double u, double p);
		int AllocateGrid();

	public:
		GridInitializer(Grid &m_grid);
		int TestInitialize(int setNo);
};

#endif
