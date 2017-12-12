#include "fdtd_1d_maxwell.h"
#include "pulse.h"
extern float dx;
extern float dt;
int time_shift=-500;
void update_B(int Nx, float **Bx, float **By,  float **Ez, float xi,
               float time_i, float speed, float tau, float w0, int bound){
    static int i;
    static int j;
    float t=(time_i+time_shift)*dt;

    for( i=0; i<Nx-1; i++)
        for( j=1; j<Nx-2;j++)
        {
            Bx[i][j] -=xi*(Ez[i][j]-Ez[i][j-1]);
            if(i>(bound-1))
                if(i<(Nx-bound+1))
            if(j==bound)
                Bx[i][j]+=xi*pulse( i*dx,  t,  speed,  tau,  w0);
            else if(j==(Nx-bound+1))
                 Bx[i][j]-=xi*pulse( i*dx,  t,  speed,  tau,  w0);
        }

    for( i=0; i<Nx-2; i++)
        for( j=0; j<Nx-1;j++)
        {
            By[i][j] -=xi*(Ez[i][j]-Ez[i+1][j]);

            if((j>(bound-1))&&(j<(Nx-bound+1)))
                if(i==(bound-1))
                    By[i][j] -=xi*pulse( (i+0.5)*dx,  t,  speed,  tau,  w0);//to correct
                else if(i==(Nx-bound))
                    By[i][j] +=xi*pulse( (i+0.5)*dx, t,  speed,  tau,  w0);//to correct
        }
}

/******************************************************************************/
void update_Dz(int Nx, float **Dz,  float **Hx,  float **Hy,  float xi,
                float time_i, float speed, float tau, float w0, int bound){
    static int i;
    static int j;
    float t=(0.5+time_i+time_shift)*dt;
    int Mx=Nx/2;
    for(i=1; i<Nx-2; i++)
        for( j=1; j<Nx-2;j++)
        {
            Dz[i][j] +=xi*(Hy[i][j]-Hy[i-1][j]+Hx[i][j]-Hx[i][j+1]);//+source*(((i==(int)(Mx*1.5))&(j==Mx))?1:0);
            if((j>(bound-1))&&(j<(Nx-bound+1)))
                if((i>(bound-1))&&(i<(Nx-bound+2)))
                {
                    if(i==bound)
                        Dz[i][j]+=xi*pulse( (i-0.5)*dx,  t,  speed,  tau,  w0);
                    else if(i==(Nx-bound+1))
                        Dz[i][j]-=xi*pulse( (i-0.5)*dx,  t,  speed,  tau,  w0);

//                    if(j==(bound-1))
//                        Dz[i][j] +=xi*pulse( i*dx,  t,  speed,  tau,  w0);
//                    else if(j==(Nx-bound))
//                        Dz[i][j] -=xi*pulse( i*dx,  t,  speed,  tau,  w0);
                }
        }

}
