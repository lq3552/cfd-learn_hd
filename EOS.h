/* handlers of equation of states */
#ifndef EOS_H
#define EOS_H

int EOS(Grid &grid, double *p,double *cs);
int pEOS(double d,double p,double &e,double &cs);

#endif
