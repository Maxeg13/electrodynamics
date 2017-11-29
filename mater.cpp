#include<stdio.h>
#include"constants.h"
/******************************************************************************/
extern float dt;
extern float w0;
float eta0=0.4;

void create_etax(int Nx, int width, float **eta){

    for(int i=0; i<Nx; i++)
        for(int j=0;j<Nx;j++)
        {
            if(i>(Nx-width))
                eta[i][j] = eta0*(i-(Nx-width))*(i-(Nx-width))/width/width;
            if(i<width)
                eta[i][j]= eta0*(i-width)*(i-width)/width/width;
        }
}


void create_etay(int Nx, int width, float **eta){

    for(int i=0; i<Nx; i++)
        for(int j=0;j<Nx;j++)
        {
            if(j>(Nx-width))
                eta[i][j] = eta0*(j-(Nx-width))*(j-(Nx-width))/width/width;
            if(j<width)
                eta[i][j]= eta0*(j-width)*(j-width)/width/width;
        }
}


void save_mas(int Nx, float** y, float ** x)
{
    int i;
    int j;
    for ( i=0;i<Nx;i++)
        for(j=0;j<Nx;j++)
            y[i][j]=x[i][j];
}
/******************************************************************************/
void update_Ez(int Nx, float **Ez, float **Ez2,float **Ez3,
               float **Dz, float** Dz2, float** Se,  float** etax, float** etay){
    //be carefull, there are some troubles
    //remember, its behavior is not like in the maxwell
    int i;
    int j;
    for(i=0;i<Nx;i++)
        for(j=0;j<Nx;j++)
        {
            Se[i][j]+=Ez3[i][j];//wrong?
            Ez[i][j]=((Dz[i][j]-Dz2[i][j])/1.+Ez2[i][j]*(1-etax[i][j]-
                                                         etay[i][j]-3*etax[i][j]*etay[i][j])
                      -4*etax[i][j]*etay[i][j]*Se[i][j])
                    /(1+etax[i][j]+
                      etay[i][j]+etax[i][j]*etay[i][j]);

            //            Se[i][j]+=Ez2[i][j];//wrong?
            //            Ez[i][j]=((Dz[i][j]-Dz2[i][j])/1.+Ez2[i][j]*(1-etax[i][j]-
            //                                                         etay[i][j])
            //                      -4*etax[i][j]*etay[i][j]*Se[i][j])
            //                    /(1+etax[i][j]+
            //                      etay[i][j]+2*etax[i][j]*etay[i][j]);


        }
}

void update_Hx(int Nx, float **Hx, float** Hx2,
               float **Bx,float **Bx2,
               float **etax,  float** etay){
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
               float **By,float **By2,
               float **etax,  float** etay){
    int i, j;
    for(i=0; i<Nx; i++)
        for(j=0;j<Nx;j++)
        {
            Hy[i][j]=(1-etax[i][j])/(1+etax[i][j])*Hy2[i][j]
                    +(1+etay[i][j])/(1.*(1+etax[i][j]))*By[i][j]
                    -(1-etay[i][j])/(1.*(1+etax[i][j]))*By2[i][j];
        }
}
