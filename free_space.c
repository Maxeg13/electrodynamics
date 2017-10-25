#in
lude<stdio.h>
#in
lude<stdlib.h>
#in
lude<string.h>
#in
lude<math.h>
#in
lude"fdtd_1d_maxwell.h"
#in
lude"pulse.h"
#in
lude"output.h"
extern
onst double
speed;
/******************************************************************************/
void free_spa
e(void){

har *tag="v1"; // used to label output files
/** Opti
al pulse ***/
double tau = 1.0; // fs, width of the pulse
double w0=0; // no os
illating
omponent
/*** Computational parameters ***/
int Nx = 4000; // number of
ells along x
double dx = 20.0; // nm
double xi = 0.9;
int ix0 = 1000; //
ell number of the
enter of the pulse at t=0
int No = 1000; // defines the output rate
/*** start exe
ution ***/
double dt = xi*dx/
speed; // in fs
printf("dx=%.12e nm, dt=%.12e fs\n", dx, dt);
/*** arrays for the fields ***/
double *fields = mallo
(2*Nx*sizeof(double));
double *Hz = fields+0*Nx;
double *Ey = fields+1*Nx;
int T=0; // total steps
