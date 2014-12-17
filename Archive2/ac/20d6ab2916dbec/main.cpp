#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#define N 500

main() {
int i,j,k;
double A[N][N], B[N][N], C[N][N], w;
struct timeval tt0, tt1, tt2;
double tt;
// Inicializacion de las matrices
for (i=0;i<N;i++)
for (j=0;j<N;j++) {
A[i][j] = sin(w);
B[i][j] = cos(w);
w=w+0.1;
C[i][j] = 0;
}
// Medida de tiempo
gettimeofday(&tt0, NULL);
gettimeofday(&tt1, NULL);
// Codigo con anidamiento ijk
for(i=0;i<N;i++)
for(j=0;j<N;j++)
for(k=0;k<N;k++)
C[i][j] += A[i][k] * B[k][j];
// Medida de tiempo
gettimeofday(&tt2, NULL);
tt=(tt2.tv_sec+tt2.tv_usec/1000000.0)-2*(tt1.tv_sec+tt1.tv_usec/1000000.0)+tt0.tv_sec+tt0.tv_usec/1000000.0;
w=0;
for(i=0;i<N;i++)
for(j=0;j<N;j++)
w += C[i][j];
// Impresion de los resultados
printf("Result = %e\n",w);
printf("Time %f\n",tt);
} // Final