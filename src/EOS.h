/* handlers of equation of states */
#ifndef EOS_H
#define EOS_H

int EOS(Grid &grid, double *p,double *cs); // TODO: the relation between EOS and Grid class is bad, reconsider it
int pEOS(double d,double p,double &e,double &cs);

#endif
