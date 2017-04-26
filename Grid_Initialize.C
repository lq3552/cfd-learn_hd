#include <math.h>
#include <stdio.h>
#include "global.h"
#include "EOS.h"

int Grid_Test1Initialize();
int Grid_Test2Initialize();
int Grid_Test3Initialize();
int Grid_Test4Initialize();
int Grid_Test5Initialize();

int Grid_Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	printf("Problem Type: %d\n",ProblemType);
	Grid = new double*[4];
	for (i = 0; i < 4; i++)
		Grid[i] = new double[size];
	switch (ProblemType){
		case 1:
			if (Grid_Test1Initialize() != SUCCESS)
				return FAIL;
			break;
		case 2:
			if (Grid_Test2Initialize() != SUCCESS)
				return FAIL;
			break;
		case 3:
			if (Grid_Test3Initialize() != SUCCESS)
				return FAIL;
			break;
		case 4:
			if (Grid_Test4Initialize() != SUCCESS)
				return FAIL;
			break;
		case 5:
			if (Grid_Test5Initialize() != SUCCESS)
				return FAIL;
			break;
		default:
			RETURNFAIL("Unsupported ProblemType!\n");
	}
	return SUCCESS;
}

int Grid_Test1Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double dL = 1.0,uL = 0.75,pL = 1.0,eL;
	double dR = 0.125,uR = 0.0,pR = 0.1,eR;
	double cs;// useless in this initializer
	StopTime = 0.20;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		if (i<=0.3*GridDimension){
			Grid[DensNum][i] = dL;
			Grid[Vel1Num][i] = uL;
			Grid[GENum][i] = eL;
			Grid[TENum][i] = eL + 0.5*dL*uL*uL;
		}
		else{
			Grid[DensNum][i] = dR;
			Grid[Vel1Num][i] = uR;
			Grid[GENum][i] = eR;
			Grid[TENum][i] = eR + 0.5*dR*uR*uR;
		}
	}
	return SUCCESS;
}

int Grid_Test2Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double dL = 1.0,uL = -2.0,pL = 0.4,eL;
	double dR = 1.0,uR = 2.0,pR = 0.4,eR;
	double cs;// useless in this initializer
	StopTime = 0.15;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		if (i<=0.5*GridDimension){
			Grid[DensNum][i] = dL;
			Grid[Vel1Num][i] = uL;
			Grid[GENum][i] = eL;
			Grid[TENum][i] = eL + 0.5*dL*uL*uL;
		}
		else{
			Grid[DensNum][i] = dR;
			Grid[Vel1Num][i] = uR;
			Grid[GENum][i] = eR;
			Grid[TENum][i] = eR + 0.5*dR*uR*uR;
		}
	}
	return SUCCESS;
}

int Grid_Test3Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double dL = 1.0,uL = 0.0,pL = 1000.0,eL;
	double dR = 1.0,uR = 0.0,pR = 0.01,eR;
	double cs;// useless in this initializer
	StopTime = 0.012;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		if (i<=0.5*GridDimension){
			Grid[DensNum][i] = dL;
			Grid[Vel1Num][i] = uL;
			Grid[GENum][i] = eL;
			Grid[TENum][i] = eL + 0.5*dL*uL*uL;
		}
		else{
			Grid[DensNum][i] = dR;
			Grid[Vel1Num][i] = uR;
			Grid[GENum][i] = eR;
			Grid[TENum][i] = eR + 0.5*dR*uR*uR;
		}
	}
	return SUCCESS;
}

int Grid_Test4Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double dL = 5.99924,uL = 19.5975,pL = 460.894,eL;
	double dR = 5.99242,uR = -6.19633,pR = 46.0950,eR;
	double cs;// useless in this initializer
	StopTime = 0.035;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		if (i<=0.4*GridDimension){
			Grid[DensNum][i] = dL;
			Grid[Vel1Num][i] = uL;
			Grid[GENum][i] = eL;
			Grid[TENum][i] = eL + 0.5*dL*uL*uL;
		}
		else{
			Grid[DensNum][i] = dR;
			Grid[Vel1Num][i] = uR;
			Grid[GENum][i] = eR;
			Grid[TENum][i] = eR + 0.5*dR*uR*uR;
		}
	}
	return SUCCESS;
}

int Grid_Test5Initialize(){
	int i,size = GridDimension + 2*NumberofGhostZones;
	double dL = 1.0,uL = -19.59745,pL = 1000.0,eL;
	double dR = 1.0,uR = -19.59745,pR = 0.01,eR;
	double cs;// useless in this initializer
	StopTime = 0.012;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);
	for (i = NumberofGhostZones; i < GridDimension + NumberofGhostZones; i++){
		if (i<=0.8*GridDimension){
			Grid[DensNum][i] = dL;
			Grid[Vel1Num][i] = uL;
			Grid[GENum][i] = eL;
			Grid[TENum][i] = eL + 0.5*dL*uL*uL;
		}
		else{
			Grid[DensNum][i] = dR;
			Grid[Vel1Num][i] = uR;
			Grid[GENum][i] = eR;
			Grid[TENum][i] = eR + 0.5*dR*uR*uR;
		}
	}
	return SUCCESS;
}
