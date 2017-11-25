#ifndef FDTD_1D_MAXWELL_H
#define FDTD_1D_MAXWELL_H
void update_B(int Nx, float **Bx, float **By, float **Ez, float xi);
void update_Dz(int Nx, float **Dz, float **Hx,  float **Hy, float source, float xi);
#endif // FDTD_QD_MAXWELL_H
