#ifndef RFOURIER_C
#define RFOURIER_C
#include<stdio.h>
#include<math.h>
#include<complex.h>

typedef double complex dcomplex;
extern const double speed, pi;

/******************************************************************************/

/******************************************************************************/
void rfourier2(double wmin, double wmax, int Nw, dc
               omplex *ft1, dc
               omplex *ft2,
               double Ey1, double Ey2, double dt, double time){

    double dw = (wmax-wmin)/(Nw-1.0);
    double mult=dt/(2*pi);
    for(int n=0; n<Nw; n++){
        double w=wmin+dw*n;
        dcomplex e=mult*exp(I*w*time);
        ft1[n] += e*Ey1;
        ft2[n] += e*Ey2;
    }
}

#endif // RFOURIER_C
