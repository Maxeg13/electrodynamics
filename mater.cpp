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
void update_Ez(int Nx, float **Ez, float **Ez2,
               const float **Dz, const float** Dz2, float** Se,  const float** etax, const float** etay){
    //be carefull, there are the troubles
    //remember, it's behavior is not like in the maxwell
    int i;
    int j;
    for(i=0;i<Nx;i++)
        for(j=0;j<Nx;j++)
        {
            Se[i][j]+=E[i][j];//wrong?
            Ez[i][j]=((Dz[i][j]-Dz2[i][j])/1.+Ez2[i][j]*(1-etax[i][j]-
                                                         etay[i][j]-3*etax[i][j]*etay[i][j])
                      -4*etax[i][j]*etay[i][j]*Se[i][j])
                    /(1+etax[i][j]+
                      etay[i][j]+etax[i][j]*etay[i][j]);
        }
}

void update_Hx(int Nx, float **Hx, float** Hx2,
               const float **Bz,const float **Bz2,
               const float **etax,  float** etay){
    for(i=0; i<Nx; i++)
        for(j=0;j<Nx;j++)
        {
            Hx[i][j]=(1-etay[i][j])/(1+etay[i][j])*Hx2[i][j]
            +(1+etax[i][j])/(1.*(1+etay[i][j]))*Bx[i][j]
            -(1-etax[i][j])/(1.*(1+etay[i][j]))*Bx2[i][j];
        }
}
