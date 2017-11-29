#include<stdio.h>
#include"constants.h"
/******************************************************************************/
extern float dt;
extern float w0;

void create_slab(int Nx, float **eps){
    for(int i=0; i<Nx; i++){
        for(int j=0;j<Nx;j++)
            eps[i][j] = 0;
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
            Se[i][j]+=Ez[i][j];//wrong?
            Ez[i][j]=((Dz[i][j]-Dz2[i][j])/1.+Ez2[i][j]*(1-etax[i][j]-
                                                         etay[i][j]-3*etax[i][j]*etay[i][j])
                      -4*etax[i][j]*etay[i][j]*Se[i][j])
                    /(1+etax[i][j]+
                      etay[i][j]+etax[i][j]*etay[i][j]);
        }
}

void update_Hx(int Nx, float **Hx, float** Hx2,
               const float **Bx,const float **Bx2,
               const float **etax,  float** etay){
    int i, j;
    for(i=0; i<Nx; i++)
        for(j=0;j<Nx;j++)
        {
            Hx[i][j]=(1-etay[i][j])/(1+etay[i][j])*Hx2[i][j]
                    +(1+etax[i][j])/(1.*(1+etay[i][j]))*Bx[i][j]
                    -(1-etax[i][j])/(1.*(1+etay[i][j]))*Bx2[i][j];
        }
}

void update_Hy(int Nx, float **Hy, float** Hy2,
               const float **By,const float **By2,
               const float **etax,  float** etay){
    int i, j;
    for(i=0; i<Nx; i++)
        for(j=0;j<Nx;j++)
        {
            Hy[i][j]=(1-etax[i][j])/(1+etax[i][j])*Hy2[i][j]
                    +(1+etay[i][j])/(1.*(1+etax[i][j]))*By[i][j]
                    -(1-etay[i][j])/(1.*(1+etax[i][j]))*By2[i][j];
        }
}
