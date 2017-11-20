#include "fdtd_1d_maxwell.h"
void update_Bz(int Nx, double *Bz, const double *Ey, const double& EL, const double& ER, int i1,int i2, double xi){

    for(int i=1; i<Nx; i++){
        switch(i)
        {
        case i1-1:
            Bz[i] +=-xi*(Ey[i+1]-Ey[i]-EL);
        case i2-1:
            Bz[i] +=-xi*(Ey[i+1]-Ey[i]+ER);
        default:
            Bz[i] +=-xi*(Ey[i+1]-Ey[i]);
        }
    }
    int i=Nx-1; // last point
    Bz[i] +=-xi*(0.0 - Ey[i]);

    //    Bz[0]=0;


    //        for(int i=1; i<Nx-1; i++){
    //            Bz[i] +=-xi*(Ey[i+1]-Ey[i]);
    //        }
    //        int i=Nx-1; // last point
    //    Bz[i]=0;

    //    Bz[Nx-1]=Bz[Nx-2];
    //    for(int i=0; i<Nx-1; i++){
    //        Bz[i] +=-xi*(Ey[i+1]-Ey[i]);
    //    }
    //    int i=Nx-1; // last point
    ////    Bz[i] +=-xi*(0.0 - Ey[i]);
}

/******************************************************************************/
void update_Dy(int Nx, double *Dy,const double *Hz, const double& HL,const double& HR, int i1, int i2, double xi){

    for(int i=1; i<Nx; i++){
        switch(i)
        {
        case i1:
            Dy[i] +=-xi*(Hz[i]-Hz[i-1]-HL);
        case i2+1:
            Dy[i] +=-xi*(Hz[i]-Hz[i-1]+HR);
        default:
            Dy[i] +=-xi*(Hz[i]-Hz[i-1]);
        }
    }
    //    Dy[Nx-1]=0;


    //    Dy[Nx-1]=Dy[Nx-2];
    //    for(int i=1; i<(Nx-1); i++){
    //        Dy[i] +=-xi*(Hz[i]-Hz[i-1]);
    //    }

}
