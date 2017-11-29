#ifndef MATER_H
#define MATER_H
void update_Ey(int Nx, float **Ey,
               const float **Dy,const float** Se,
               const float **, const float**);
void save_mas(int Nx, float* Dy2, float * Dy);
void update_Hz(int Nx, float *Hz,
               const float *Bz,const float *Bz2,
               const float *mu,  float* eta);
void create_slab(int Nx, float *eps, float *eta, int j1, int j2, float eslab);

#endif // MATER_H
