#ifndef MATER_H
#define MATER_H
void update_Ey(int Nx, double *Ey,
               const double *Dy,const double* Dy2,
               const double *ebkg, const double*);
void save_mas(int Nx, double* Dy2, double * Dy);
void update_Hz(int Nx, double *Hz,
               const double *Bz,const double *Bz2,
               const double *mu,  double* eta);
void create_slab(int Nx, double *eps, double *eta, int j1, int j2, double eslab);

#endif // MATER_H
