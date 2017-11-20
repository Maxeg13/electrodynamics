#ifndef PULSE_H
#define PULSE_H
double pulse(double x, double t, double speed, double tau, double w0);
void getEHL(double& E0, double& H0, int ti, int i, int ix0, double dx, double dt, double speed, double tau, double w0);
void getEHR(double& E0, double& H0, int ti, int i, int ix0, double dx, double dt, double speed, double tau, double w0);

/******************************************************************************/
void create_initial_dist(int Nx, double *Ey, double *Hz, double dx, double dt,
                         double speed, int ix0, double tau, double w0, int dir);
void create_initial_monochrom(double *Ey, double *Hz, double dx, float k, float l, int dir);
#endif // PULSE_H
