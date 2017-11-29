#ifndef MATER_H
#define MATER_H

void update_Ez(int Nx, float **Ez, float **Ez2, float **Ez3,
               float **Dz, float** Dz2, float** Se,  float** etax, float** etay);

void save_mas(int Nx, float** y, float ** x);


void update_Hx(int Nx, float **Hx, float** Hx2,
               float **Bx,float **Bx2,
               float **etax,  float** etay);

void update_Hy(int Nx, float **Hy, float** Hy2,
               float **Bz,float **Bz2,
               float **etax,  float** etay);


void create_etax(int Nx, int width, float **eta);

void create_etay(int Nx, int width, float **eta);

#endif // MATER_H
