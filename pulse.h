#ifndef PULSE_H
#define PULSE_H
float pulse(float x, float t, float speed, float tau, float w0);
void getEHL(float& E0, float& H0, int ti, int i, int ix0, float dx, float dt, float speed, float tau, float w0);
void getEHR(float& E0, float& H0, int ti, int i, int ix0, float dx, float dt, float speed, float tau, float w0);

/******************************************************************************/
void create_initial_dist(int Nx, float *Ey, float *Hz, float dx, float dt,
                         float speed, int ix0, float tau, float w0, int dir);
void create_initial_monochrom(float *Ey, float *Hz, float dx, float k, float l, int dir);
#endif // PULSE_H
