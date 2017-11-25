#include "fdtd_1d_maxwell.h"
void update_B(int Nx, double **Bx, double **By,  double **Ez, double xi){
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
void update_Dz(int Nx, double **Dz,  double **Hx,  double **Hy, double source, double xi){
    static int i;
    static int j;
    for(i=1; i<Nx-2; i++)
        for( j=0; j<Nx-2;j++)
            Dz[i][j] +=-xi*(Hx[i+1][j]+Hy[i][j]-Hx[i][j]-Hy[i][j+1])+source;
}
