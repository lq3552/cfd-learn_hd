/* declare the prototypes of solver-related functions */

int Boundary(double *d, double *E, double *e, double *u, double *p, double *cs, double **U,
		int GridRank,int* GridDimension,int NumberofGhostZones);
int Hydro_TimeStep(double dx, double time, double *u, double *cs, double &dt,
		int GridRank,int* GridDimension,int NumberofGhostZones);
int Flux(double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,
		int GridRank,int* GridDimension,int NumberofGhostZones);
int Hydro_Update(double dx, double dt, double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,
		int GridRank,int* GridDimension,int NumberofGhostZones);

/* Riemann solver */
extern int Riemann(double *WL, double cL, double *WR, double cR, double *WS);
