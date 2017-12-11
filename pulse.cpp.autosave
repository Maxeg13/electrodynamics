#include<stdio.h>
#include<math.h>
#include "pulse.h"

/******************************************************************************/
float pulse(float x, float t, float speed, float tau, float w0){
    float t1 = t - x/speed;
    float a = t1/tau;
    return exp(-a*a)*cos(w0*t1);
}

/******************************************************************************/
void create_initial_dist(int Nx, float *Ey, float *Hz, float dx, float dt,
                         float speed, int ix0, float tau, float w0,int dir){


    for(int i=0; i<Nx; i++){
        Ey[i] += pulse(dx*(i+0.0-ix0), 0*dt, speed, tau, w0);
        Hz[i] += dir*pulse(dx*(i+0.5-ix0), -0.5*dt, speed, tau, w0);
    }
    Ey[0]=0; // to satisfy b.

}

void getEHL(float& E0, float& H0, int ti, int i, int ix0, float dx, float dt, float speed, float tau, float w0)
{
//    static int ti=0;

    E0=pulse(dx*(i+0.0-ix0), ti*dt, speed, tau, w0);
    H0=pulse(dx*(i-0.5-ix0), (ti+0.5)*dt, speed, tau, w0);
}


void getEHR(float& E0, float& H0, int ti, int i, int ix0, float dx, float dt, float speed, float tau, float w0)
{
//    static int ti=0;

    E0=pulse(dx*(i+0.0-ix0), ti*dt, speed, tau, w0);
    H0=pulse(dx*(i-0.5-ix0), (ti+0.5)*dt, speed, tau, w0);
}

void create_initial_monochrom(float *Ey, float *Hz, float dx,float k,float l,int dir)
{
    for(int i=0; (i*dx)<l; i++)
    {
        Ey[i] += (sin(dx*k*(i+0.0)))/2;
        Hz[i] += dir*(sin(dx*k*(i+0.5)))/2;
    }
}
