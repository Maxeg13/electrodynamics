#include "fdtd_1d_maxwell.h"
#include "pulse.h"
extern float dx;
//extern float dt;
void update_B(int Nx, float **Bx, float **By,  float **Ez, float xi,
              float x, float t, float speed, float tau, float w0, int width){
    static int i;
    static int j;

    for( i=0; i<Nx-1; i++)
        for( j=1; j<Nx-2;j++)
            Bx[i][j] -=xi*(Ez[i][j]-Ez[i][j-1]);

    for( i=0; i<Nx-2; i++)
        for( j=0; j<Nx-1;j++)
        {
            By[i][j] -=xi*(Ez[i][j]-Ez[i+1][j]);

            if((j>(width-2))&&(j<(Nx-width+1)))
                if(i==(width-1))
                    By[i][j] -=xi*pulse( (i+1)*dx,  t,  speed,  tau,  w0);//to correct
                else if(i=(Nx-width))
                    By[i][j] +=xi*pulse( (i+1)*dx,  t,  speed,  tau,  w0);//to correct
        }
}

/******************************************************************************/
void update_Dz(int Nx, float **Dz,  float **Hx,  float **Hy, float source, float xi,
               float x, float t, float speed, float tau, float w0, int width){
    static int i;
    static int j;
    int Mx=Nx/2;
    for(i=1; i<Nx-2; i++)
        for( j=1; j<Nx-2;j++)
        {
            Dz[i][j] +=xi*(Hy[i][j]-Hy[i-1][j]+Hx[i][j]-Hx[i][j+1]);//+source*(((i==(int)(Mx*1.5))&(j==Mx))?1:0);
            if((j>(width-2))&&(j<(Nx-width+1)))
                if((i>(width-1))&&(i<(Nx-width+2)))
                {
                    if(i==width)
                        Dz[i][j]-=xi*pulse( (i-1)*dx,  t,  speed,  tau,  w0);
                    else if(i==(Nx-width+1))
                        Dz[i][j]+=xi*pulse( (i-1)*dx,  t,  speed,  tau,  w0);

                    if(j==(width-1))
                        Dz[i][j] +=xi*pulse( i*dx,  t,  speed,  tau,  w0);
                    else if(j==(Nx-width))
                        Dz[i][j] -=xi*pulse( i*dx,  t,  speed,  tau,  w0);
                }
        }

}
