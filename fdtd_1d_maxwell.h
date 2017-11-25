#ifndef FDTD_1D_MAXWELL_H
#define FDTD_1D_MAXWELL_H
void update_B(int Nx, double **Bx, double **By, double **Ez, double xi);
void update_Dz(int Nx, double **Dz, double **Hx,  double **Hy, double source, double xi);
#endif // FDTD_QD_MAXWELL_H
