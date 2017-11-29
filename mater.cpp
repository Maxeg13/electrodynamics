#include<stdio.h>
#include"constants.h"
/******************************************************************************/
extern float dt;
extern float w0;

void create_slab(int Nx, float *eps, float *eta, int j1, int j2, float eslab){
    for(int i=0; i<Nx; i++){
        eps[i] = 1;
        eta[i]=0;
    }
    //    for(int i=j1; i<j2+1; i++){
    //        eps[i] = eslab;
    //    }
    for(int i=j1; i<j2; i++){
        eps[i] = eslab;
        //        eta[i]=(i-j1)*2*pi*dt*2*w0/(Nx-j1)/20;
        eta[i]=0;
    }



}
void save_mas(int Nx, float** y, const float ** x)
{
    int i;
    int j;
    for ( i=0;i<Nx;i++)
        for(j=0;j<Nx;j++)
        y[i][j]=x[i][j];
}
/******************************************************************************/
void update_Ez(int Nx, float **Ez,
               const float **Dz, const float** Dz2, float** Se,  const float** etax, const float** etay){
    //be carefull, there are the troubles
    int i;
    int j;
    for(i=0;i<Nx;i++)
        for(j=0;j<Nx;j++)
        {
            Se[i][j]+=E[i][j];//wrong?
            Ez[i][j]=((Dz[i][j]-Dz2[i][j])/1.+Ez[i][j]*(1-etax[i][j]
                 -etay[i][j])-4*teax[i][j]*etay[i][j]*Se[i][j])
                /(1+etax[i][j]+
                etay[i][j]+2*etax[i][j]*etay[i][j]);
        }
}

void update_H(int Nx, float *Hz,
              const float *Bz,const float *Bz2,
              const float *mu,  float* eta){
    for(int i=0; i<Nx; i++)
    {
        float k=1;
        //        eta[i]*=k;
        Hz[i]=((mu[i]-k*eta[i])/(mu[i]+k*eta[i]))*Hz[i]+(Bz[i]-Bz2[i])/(mu[i]+k*eta[i]);
        //        eta[i]/=k;
    }
}
