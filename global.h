#define SUCCESS 0
#define FAIL 1
#define TINY 1e-16
#define RETURNFAIL(x) {printf("%s",x);return FAIL;}
#define TOL 1e-6
#define MAX_LINE_LENGTH 100

// In the final stage you'll change this to a format like enzo class, but now it's process-oriented :(

/*extern int Grid_Initialize();
extern int GodunovSolver(); 
extern int Output();
extern int EOS(double *d,double *e, double *p,double *cs);
extern int pEOS(double p,double &e);*/

/* Problem parameters  */
extern int ProblemType;

/* Top grid parameters */
extern int GridRank; 
extern int GridDimension;
extern int NumberofGhostZones;
extern double **Grid;

/* data field index */
extern int DensNum,TENum,GENum,Vel1Num;

/* Units [cgs] */
extern double LengthUnit,TimeUnit,DensityUnit;

/* Hydrodynamics parameter */
extern int Solver;
extern int RiemannIteration;
extern int BoundaryCondition;

/* Thermal dynamics parameter */
extern int EOSType;
extern float Gamma;
extern float Mu;

/* Time step */
extern float CourantNumber;
extern double StopTime;
extern int StopCycle;

/* Output */
extern char* DataDump; //prefix of output
extern double dtDump; // cycle of output
