#ifndef MATER_H
#define MATER_H
void update_Ey(int Nx, double *Ey,
               const double *Dy,const double* Dy2,
               const double *ebkg, const double*);
void save_Dy2(int Nx, double* Dy2, double * Dy);

void create_slab(int Nx, double *eps, double *eta, int j1, int j2, double eslab);

#endif // MATER_H
