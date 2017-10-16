#include <math.h>
#include <stdio.h>
#include "global.h"
#include "grid.h"

//EOS's relation with grid is a bit messy! improbe it!

int EOS(double *d,double *e, double *p,double *cs){// Only support ideal gas for now
	int i,size=1;
	for (i = 0; i < Grid.GridRank; i++)
		size *= Grid.GridDimension[i] + 2*Grid.NumberofGhostZones;
	if (EOSType == 1){ // ideal gas
		for (i = 0; i < size; i++){
			p[i] = e[i]*(Gamma-1);
			cs[i] = sqrt(Gamma*p[i]/d[i]);
		}
		return SUCCESS;
	}
	else
		return FAIL;
}

int pEOS(double d, double p, double &e, double &cs){// Only support ideal gas for now
	if (EOSType == 1){ // ideal gas
		e = p/(Gamma-1);
		cs = sqrt(Gamma*p/d);
		return SUCCESS;
	}
	else
		return FAIL;
}
