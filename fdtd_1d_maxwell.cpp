#include "fdtd_1d_maxwell.h"
void update_B(int Nx, float **Bx, float **By,  float **Ez, float xi){
static int i;
static int j;
    for( i=0; i<Nx-1; i++)
        for( j=0; j<Nx-2;j++)
            Bx[i][j] +=xi*(Ez[i][j+1]-Ez[i][j]);

    for( i=0; i<Nx-2; i++)
        for( j=0; j<Nx-1;j++)
            Bx[i][j] +=xi*(Ez[i][j]-Ez[i+1][j]);

//    int i=Nx-1; // last point
//    Bz[i] +=-xi*(0.0 - Ey[i]);

}

/******************************************************************************/
void update_Dz(int Nx, float **Dz,  float **Hx,  float **Hy, float source, float xi){
    static int i;
    static int j;
    int Mx=Nx/2;
    for(i=1; i<Nx-2; i++)
        for( j=0; j<Nx-2;j++)
            Dz[i][j] +=-xi*(Hx[i+1][j]+Hy[i][j]-Hx[i][j]-Hy[i][j+1])+source*(((i==Mx)&(j==Mx))?1:0);
}
