#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <omp.h>
#include <errno.h>

double fonction1(double var1)
{
    var1=3.0;
    printf("la valeur de var1 =%g \n",var1);
    return  0;
}

double fonction2(double n,double* var1,double* var2)
{
    *var1=n*(*var1);
    *var2=n*(*var2);
    printf("la valeur de var1 =%g var2 =%g \n",*var1,*var2);
    return  0;
}
int main()
{
    double var1=3.0;
    double var2=2.0;
   // fonction1(var1);

    //printf("la velur de var1 apres application de fonc1 = %g \n",var1);

    fonction2(3,&var1,&var2);
    fonction2(2,&var1,&var2);
    printf("la velur de var1 apres application de fonc2 var1 = %g et var2 = %g \n",var1,var2);
    return 0;
}
