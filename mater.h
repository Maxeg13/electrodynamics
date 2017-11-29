#ifndef MATER_H
#define MATER_H
void update_Ez(int Nx, float **Ez, float ** Ez2,
               const float **Dy, const float** ,float** Se,
               const float **, const float**);
void save_mas(int Nx, float* Dy2, float * Dy);


void update_Hx(int Nx, float **Hx, float** Hx2,
               const float **Bx,const float **Bx2,
               const float **etax,  float** etay);

void update_Hy(int Nx, float **Hy, float** Hy2,
               const float **Bz,const float **Bz2,
               const float **etax,  float** etay);


void create_slab(int Nx, float **eps);

#endif // MATER_H
