#include<stdio.h>
#include<math.h>
#include "pulse.h"

/******************************************************************************/
double pulse(double x, double t, double speed, double tau, double w0){
    double t1 = t - x/speed;
    double a = t1/tau;
    return exp(-a*a)*cos(w0*t1);
}

/******************************************************************************/
void create_initial_dist(int Nx, double *Ey, double *Hz, double dx, double dt,
                         double speed, int ix0, double tau, double w0,int dir){


    for(int i=0; i<Nx; i++){
        Ey[i] += pulse(dx*(i+0.0-ix0), 0*dt, speed, tau, w0);
        Hz[i] += dir*pulse(dx*(i+0.5-ix0), -0.5*dt, speed, tau, w0);
    }
    Ey[0]=0; // to satisfy b.

}



void create_initial_monochrom(double *Ey, double *Hz, double dx,float k,float l,int dir)
{
    for(int i=0; (i*dx)<l; i++)
    {
        Ey[i] += (sin(dx*k*(i+0.0)))/2;
        Hz[i] += dir*(sin(dx*k*(i+0.5)))/2;
    }
}
