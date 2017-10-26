//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<math.h>
////#include"fdtd_1d_maxwell.h"
////#include"pulse.h"
////#include"output.h"
//extern const double speed;
///******************************************************************************/
//void free_space(void){

//    char *tag="v1"; // used to label output files
//    /** Opti
//        al pulse ***/
//    double tau = 1.0; // fs, width of the pulse
//    double w0=0; // no os

//    /*** Computational parameters ***/
//    int Nx = 4000; // number of

//    double dx = 20.0; // nm
//    double xi = 0.9;
//    int ix0 = 1000; //

//    int No = 1000; // defines the output rate
//    /*** start exe
//        ution ***/
//    double dt = xi*dx/speed; // in fs
//    printf("dx=%.12e nm, dt=%.12e fs\n", dx, dt);
//    /*** arrays for the fields ***/
//    double *fields = malloc(2*Nx*sizeof(double));
//    double *Hz = fields+0*Nx;
//    double *Ey = fields+1*Nx;
//    int T=0; // total steps

//    reate_initial_dist(Nx, Ey, Hz, dx, dt,
//                       speed, ix0, tau, w0);
//    output_Ey_vs_x(Nx, Ey, 0, dx, tag);

//    for(;;){
//        printf("Number of steps to run (<=0 to exit) -> "); fflush(stdout);
//        int steps;
//        scanf("%d", &steps);
//        if(steps<=0) break;

//        printf("Making %d steps\n", steps);
//        for(int n=0; n<steps; n++, T++){
//            update_Bz(Nx, Hz, Ey, xi); // find Bz at n+1/2
//            update_Dy(Nx, Ey, Hz, xi); // find Ey at n+1

//            /* output of Hz */
//            if((T+1)%No == 0){
//                printf("Elapsed time -> %g fs (%d steps)\n", dt*(T+1), T+1);
//                output_Ey_vs_x(Nx, Ey, T+1, dx, tag);
//            }

//        }// end of n loop
//    }// end of global loop


//    free(fields);
//}

///*****************************************************************************/
//int main(void){

//    free_space();

//    return 0;
//}
