#include<stdio.h>
#include"constants.h"
/******************************************************************************/
extern double dt;
extern double w0;
void create_slab(int Nx, double *eps, double *eta, int j1, int j2, double eslab){
    for(int i=0; i<Nx; i++){
        eps[i] = 1;
        eta[i]=0;
    }
//    for(int i=j1; i<j2+1; i++){
//        eps[i] = eslab;
//    }
    for(int i=j1; i<Nx; i++){
        eps[i] = eslab;
        eta[i]=2*pi*dt*2*w0;
    }



}
void save_Dy2(int Nx, double* Dy2, double * Dy)
{
    for (int i=0;i<Nx;i++)
        Dy2[i]=Dy[i];
}
/******************************************************************************/
void update_Ey(int Nx, double *Ey,
               const double *Dy,const double *Dy2,
               const double *eps, const double* eta){

    for(int i=0; i<Nx; i++){
//        Ey[i] = Dy[i]/eps[i];
        Ey[i]=(eps[i]-eta[i])/(eps[i]+eta[i])*Ey[i]+(Dy2[i]-Dy[i])/(eps[i]+eta[i]);
    }
}
