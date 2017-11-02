#ifndef SET_MEM_H
#define SET_MEM_H
 #include<complex.h>
#include<stdio.h>
 #include<math.h>
//complex<double> s;

  typedef  complex<double> dcomplex;

 void zset_mem(int N, dcomplex *A, dcomplex var);
 void dset_mem(int N, double *A, double var);

#endif // SET_MEM_H
