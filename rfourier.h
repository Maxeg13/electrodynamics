#ifndef RFOURIER_H
#define RFOURIER_H
#include<complex>
#include<stdio.h>
#include<math.h>
using namespace std;
typedef  complex<double> dcomplex;
void rfourier2(double wmin, double wmax, int Nw, dcomplex *ft1, dcomplex *ft2,
               double Ey1, double Ey2, double dt, double time, bool, bool);
#endif // RFOURIER_H
