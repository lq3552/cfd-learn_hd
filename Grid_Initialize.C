#include <math.h>
#include <stdio.h>
#include "global.h"
#include "grid.h"
#include "EOS.h"

int grid::Grid_Test1Initialize(){
	int i;
	double dL = 1.0,uL = 0.75,pL = 1.0,eL;
	double dR = 0.125,uR = 0.0,pR = 0.1,eR;
	double cs;// useless in this initializer
	DensNum = 0;  
	TENum = 1; 
	GENum = 2; 
	Vel1Num = 3;
	StopTime = 0.20;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);

	this->AllocateGrid();

	for (i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++){
		if (i<=0.3*GridDimension[0]){
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

int grid::Grid_Test2Initialize(){
	int i;
	double dL = 1.0,uL = -2.0,pL = 0.4,eL;
	double dR = 1.0,uR = 2.0,pR = 0.4,eR;
	double cs;// useless in this initializer
	DensNum = 0;  
	TENum = 1; 
	GENum = 2; 
	Vel1Num = 3;
	StopTime = 0.15;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);

	this->AllocateGrid();

	for (i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++){
		if (i<=0.5*GridDimension[0]){
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

int grid::Grid_Test3Initialize(){
	int i;
	double dL = 1.0,uL = 0.0,pL = 1000.0,eL;
	double dR = 1.0,uR = 0.0,pR = 0.01,eR;
	double cs;// useless in this initializer
	DensNum = 0;  
	TENum = 1; 
	GENum = 2; 
	Vel1Num = 3;
	StopTime = 0.012;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);

	this->AllocateGrid();

	for (i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++){
		if (i<=0.5*GridDimension[0]){
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

int grid::Grid_Test4Initialize(){
	int i;
	double dL = 5.99924,uL = 19.5975,pL = 460.894,eL;
	double dR = 5.99242,uR = -6.19633,pR = 46.0950,eR;
	double cs;// useless in this initializer
	DensNum = 0;  
	TENum = 1; 
	GENum = 2; 
	Vel1Num = 3;
	StopTime = 0.035;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);

	this->AllocateGrid();

	for (i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++){
		if (i<=0.4*GridDimension[0]){
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

int grid::Grid_Test5Initialize(){
	int i;
	double dL = 1.0,uL = -19.59745,pL = 1000.0,eL;
	double dR = 1.0,uR = -19.59745,pR = 0.01,eR;
	double cs;// useless in this initializer
	DensNum = 0;  
	TENum = 1; 
	GENum = 2; 
	Vel1Num = 3;
	StopTime = 0.012;
	pEOS(dL,pL,eL,cs);
	pEOS(dR,pR,eR,cs);

	this->AllocateGrid();

	for (i = NumberofGhostZones; i < GridDimension[0] + NumberofGhostZones; i++){
		if (i<=0.8*GridDimension[0]){
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
