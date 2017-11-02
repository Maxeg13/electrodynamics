#include<complex>

typedef  complex<double> dcomplex;

/******************************************************************************/
void zset_mem(int N, dcomplex *A, dcomplex var){
    for(int i=0; i<N; i++){
        A[i]=var;
    }
}
/******************************************************************************/
void dset_mem(int N, double *A, double var){
    for(int i=0; i<N; i++){
        A[i]=var;
    }
}
