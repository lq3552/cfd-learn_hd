#!/bin/bash
g++ -ohydro.out Godunov.C Grid_Output.C SetGlobalValue.C EOS.C Grid_Initialize.C RiemannSolver.C main.C
