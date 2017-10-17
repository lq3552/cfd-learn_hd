/*Define the grid class which holds the computation domain and the relevant solver*/

class grid{

private:
/* Top grid parameters */
	int GridRank; 
	int GridDimension[MAX_DIMENSION];
	int NumberofGhostZones;
	int NumberofBaryonFields;
	double **Grid;

public:
	void SetMetaData(int m_GridRank,int m_GridDimension[MAX_DIMENSION],int m_NumberofGhostZones,int m_NumberofBaryonFields);
	void PrintMetaData(){
		printf("GridRank: %d\n",GridRank);
		printf("GridDimension = %d %d %d",GridDimension[0],GridDimension[1],GridDimension[2]);
	}
	int GodunovSolver();
    void AllocateGrid();
	int Output();
    int Grid_Test1Initialize();
    int Grid_Test2Initialize();
    int Grid_Test3Initialize();
    int Grid_Test4Initialize();
    int Grid_Test5Initialize();

	friend int EOS(double *d,double *e, double *p,double *cs);
	friend int InitializeNew();
};

extern grid Grid; // Is there a safer way to deal with grid class? Refer to enzo.c please!
