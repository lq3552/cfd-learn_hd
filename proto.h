/* declare the prototypes of solver-related functions */

#ifndef PROTO_H
#define PROTO_H
int SetParameter(Grid &grid, FILE* fptr);

int Flux(double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,
		int GridRank,int* GridDimension,int NumberofGhostZones);
int Hydro_Update(double dx, double dt, double *d, double *E, double *e, double *u, double *p, double *cs, double **U, double **F,
		int GridRank,int* GridDimension,int NumberofGhostZones);

/* Riemann solver */
int Riemann(double *WL, double cL, double *WR, double cR, double *WS);

#endif
