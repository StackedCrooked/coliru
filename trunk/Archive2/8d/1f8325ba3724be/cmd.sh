#include <stdio.h>
#include <stdlib.h>



#define N 500
#define MAXITER 10
double t1;
float X[N][N], Y[N][N];
float Z[N];
int S; 
FILE * f;

unsigned long long read_cycles()
   {
     unsigned int hi = 0, lo = 0;
     __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi) : : "memory" );
       unsigned long long that =   (unsigned long long)((lo)| (unsigned long long)(hi)<<32 );
     return that;
   }
double dtime()
{
  return (double) read_cycles();
}



double tmn (double x[], int niter ) {
  int i;
  double y =1E8;;
  for (i=0; i < niter; i++)
    if (x[i] < y)
      y= x[i];
  return (y);
}

int sumrec (int x)
{
  return (x <1 ? 0: x+sumrec(x-1));
}

int sumite(int x)
{
  int i, tmp=0;
  for (i=1; i<x; i++)
    tmp+=i;
  return tmp;
}

void foo(int x)
{
  int i;
  Z[0]=0;
  for (i=1; i<x; i++)
    Z[i]=Z[i-1]+1; 
}

void fou(int x)
{
 
  int i;
      Z[0]=0;
  for (i=1; i<x; i++)
    Z[i]=Z[0]+i; 
}

void fov(int x)
{
 
  int i;     
 for (i=0; i<x; i++)
    Z[i]=i; 
}



int main_copy_ij(int niter)
{
  double tex[MAXITER];
  int i, j, k;
  for (k=0;k<niter;k++){

    t1=dtime();
    for (i=0;i<N;i++)
      for (j=0;j<N;j++)
	Y[i][j]=X[i][j];
    tex[k]=dtime()-t1 ;
  } 

  for (k=0; k<niter ; k++)
    printf ("Temps copie par element-ij %.2E  N %d \n", tex[k]/(N*N), N);
  fprintf(f, "MIN Temps copie par element-ij %4.2f  N %d \n", tmn(tex,niter)/(N*N), N);
}

void main_copy_ji(int niter)
{
  double tex[MAXITER];
  int i, j, k;
  for (k=0;k<niter;k++){
    t1=dtime();
    for (j=0;j<N;j++)
      for (i=0;i<N;i++)
	Y[i][j]=X[i][j];
    tex[k]=dtime()-t1 ;
  } 

  for (k=0; k<niter ; k++)
    printf ("Temps copie par element-ji %.2E  N %d \n", tex[k]/(N*N), N);
  fprintf(f, "MIN Temps copie par element-ji %4.2f  N %d \n", tmn(tex, niter)/(N*N), N);

}


void sum_N(int niter)
{
  int i, j, k;
  double texR[MAXITER], texI[MAXITER];

  for (k=0;k<niter;k++){
    t1=dtime();
    S= sumrec(N);
    texR[k]=dtime()-t1 ; 
  }

  for (k=0;k<niter;k++)
    printf ("Temps somme recursive par element %.2E  N %d \n", texR[k]/N, N);
  fprintf(f, "MIN Temps somme recursive par element %4.2f  N %d \n", tmn(texR, niter)/N, N);
  
  for (k=0;k<niter;k++){
    t1=dtime();
    S= sumite(N);
    texI[k]=dtime()-t1 ;
  } 
  for (k=0;k<niter;k++)
    printf ("Temps somme iterative par element %.2E  N %d \n", texI[k]/N, N);
  fprintf(f, "MIN Temps somme iterative par element %4.2f  N %d \n", tmn(texI, niter)/N, N);
}

void enum_N(int niter)
{
  double tex[MAXITER];
  int i, j, k;
  for (k=0;k<niter;k++){
    t1=dtime();
    foo (N);
    tex[k]=dtime()-t1 ;
  } 
  for (k=0;k<niter;k++)
    printf ("recurrence/element %.2E  N %d \n", tex[k]/N, N);
  fprintf(f, "MIN recurrence/element  %4.2f  N %d \n", tmn(tex, niter)/N, N);
  
  for (k=0;k<niter;k++){
    t1=dtime();
    fou(N);
    tex[k]=dtime()-t1 ;
  } 
  for (k=0;k<niter;k++)
    printf ("addition/element %4.2f  N %d \n", tex[k]/N, N);
  fprintf(f, "MIN addition /element %4.2f  N %d \n", tmn(tex, niter)/N, N);
  
  for (k=0;k<niter;k++){
    t1=dtime();
    fov(N);
    tex[k]=dtime()-t1 ;
  }
  for (k=0;k<niter;k++)
    printf ("affectation/element %4.2f  N %d \n", tex[k]/N, N);
  fprintf(f, "MIN affectation/element %4.2f  N %d \n", tmn(tex, niter)/N, N);
}

void finAnormale() {
  printf("********** ERREUR ARGUMENT\n");
  exit(1);
}
/*main(int argc, char * argv[])*/
main()
{
  int niter = 10;
/*  if (argc <=1)
    finAnormale();
  niter = atoi(argv[1]);
  if (niter >MAXITER)
    finAnormale();*/
  f = fopen ("RES", "w");
  main_copy_ij(niter);
  main_copy_ji(niter);
  sum_N(niter);
  enum_N(niter);
  fclose (f);
 /* system("pause");*/
}