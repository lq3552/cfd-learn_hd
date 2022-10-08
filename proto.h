/* declare the prototypes of solver-related functions */

#ifndef PROTO_H
#define PROTO_H

int SetParameter(Grid &grid, FILE* fptr);
/* Riemann solver */
int Riemann(const double* const WL, const double cL, const double* const WR, const double cR, double* const WS);
int Riemann(const double* const WL, const double cL, const double* const WR, const double cR, double* const WS);

#endif
