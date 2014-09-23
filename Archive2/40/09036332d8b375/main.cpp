
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* calloc, exit, free  */
#include <string.h>     /* memset              */

int main() {
  
  int len=32;                            // length of (approximation) signal
  const int lev=4,f=2;                   // decomposition level and Haar filter length
  
  double x[len];                         // initial signal
  double sq2=1.41421356/2;               // sqrt(2)
  
  double g[f]={sq2,-sq2};                // Haar wavelet filter
  double h[f]={sq2, sq2};                // Haar scaling function
  
  for (int i=0; i<len; i++) x[i]=i;      // ramp signal
  
  double *y=calloc(len, sizeof(double)); // allocate y of 0s   
  double *t=calloc(len, sizeof(double)); // temporary work array
  
  memcpy(t, x, len*sizeof(double));      // copy x to tmp  
  for (int i=0; i<lev; i++) {            // level counter i
    memset(y, 0, len*sizeof(double));
    int len2=len/2;
    for (int j=0; j<len2; j++)           // coefficient index j
      for (int k=0; k<f; k++) {          // filter tap index k
          y[j]     +=t[2*j+k]*h[k];      // approximation
	      y[j+len2]+=t[2*j+k]*g[k];      // detail
      }
    len=len2;                            // leave the details
    memcpy(t, y, len*sizeof(double));    // copy approximation to t
  }

  for (int i=0; i<32; i++) printf ("%d %f %f\n",i,x[i],y[i]);
  // compare in matlab (using Jeffrey C. Kantor's fwt.m) with
  // >> x = 0:31, fwt ( [ sqrt(.5) sqrt(.5) ], x, 4)'
 
 free(y);                                // free allocated memory
 free(t);                                // free allocated memory
 
}
