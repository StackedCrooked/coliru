#include <math.h>
 #include <stdio.h>
 #include <stdlib.h>
 using namespace std;
 //using namespace std::complex;
 #include<complex>
 typedef complex<double> z_type;
 #define Re(x) x.real()
 #define Im(x) x.imag()
 int main(){ z_type z= z_type(.5,.5);
 z_type c=asin(z);
 printf("%9.8f %9.8f\n",Re(c),Im(c));
 }
