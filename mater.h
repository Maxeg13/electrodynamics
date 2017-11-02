#ifndef MATER_H
#define MATER_H
void update_Ey(int Nx, double *Ey,
               const double *Dy,
               const double *ebkg);
void create_slab(int Nx, double *eps, int j1, int j2, double eslab);

#endif // MATER_H
