/* declare the prototypes of solver-related functions */

#ifndef PROTO_H
#define PROTO_H

int SetParameter(Grid &grid, FILE* fptr);
/* Riemann solver */
int Riemann(double *WL, double cL, double *WR, double cR, double *WS);

#endif
