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
//        eta[i]=(i-j1)*2*pi*dt*2*w0/(Nx-j1)/20;
                eta[i]=0.4;
    }



}
void save_mas(int Nx, double* Dy2, double * Dy)
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
        Ey[i]=((eps[i]-eta[i])/(eps[i]+eta[i]))*Ey[i]+(Dy[i]-Dy2[i])/(eps[i]+eta[i]);
        //    Sums+=Ey[i];
        //        Ey[i]=(D[])/(eps[i]+eta[i]);
    }
}

void update_Hz(int Nx, double *Hz,
               const double *Bz,const double *Bz2,
               const double *mu,  double* eta){
    for(int i=0; i<Nx; i++)
    {
        double k=1;
//        eta[i]*=k;
        Hz[i]=((mu[i]-k*eta[i])/(mu[i]+k*eta[i]))*Hz[i]+(Bz[i]-Bz2[i])/(mu[i]+k*eta[i]);
//        eta[i]/=k;
    }
}
