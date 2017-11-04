#ifndef RFOURIER_C
#define RFOURIER_C
#include "constants.h"
#include "rfourier.h"
#include <complex>
#include <stdio.h>
#include <math.h>
using namespace std;

extern const double speed, pi;

/******************************************************************************/

/******************************************************************************/
void rfourier2(double wmin, double wmax, int Nw, dcomplex *ft1, dcomplex *ft2,
               double Ey1, double Ey2, double dt, double time,bool b1, bool b2){

    double dw = (wmax-wmin)/(Nw-1.0);
    double mult=dt/(2*pi);
    for(int n=0; n<Nw; n++){
        double w=wmin+dw*n;
        dcomplex e=mult*exp(dcomplex(0,1)*w*time);
        if(b1)
            ft1[n] += e*Ey1;
        if(b2)
            ft2[n] += e*Ey2;
    }
}

#endif // RFOURIER_C
