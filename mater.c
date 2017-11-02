#include<stdio.h>

/******************************************************************************/

void create_slab(int Nx, double *eps, int j1, int j2, double eslab){


    for(int i=0; i<Nx; i++){
        eps[i] = 1;
    }
    for(int i=j1; i<j2+1; i++){
        eps[i] = eslab;
    }

}

/******************************************************************************/
void update_Ey(int Nx, double *Ey,
               const double *Dy,
               const double *eps){

    for(int i=0; i<Nx; i++){
        Ey[i] = Dy[i]/eps[i];
    }
}
