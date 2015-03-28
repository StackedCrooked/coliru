#include <stdlib.h>
#include <iostream>

using namespace std;

double f1( double x ){
    return x * 1.7;
}

void calc ( double* a, double* b, int r, int c, double (*f) (double) ) 
{
    double input;
    double output;

    for(int i=0;i<r*c;i++)
    {
        input=a[i];
        output=(*f)(input);
        b[i]=output;
    }
}

int main()
{
    //input array:
    int r=3;
    int c=4;
    double* a = new double[r*c];
    double* b = new double[r*c];

    //fill "a" with test data
    //...

    for (int i=0;i<r*c;i++)
    {
        a[i]=i;
    }


    //transform a to b
   calc ( a, b, r, c, f1 );

    //print to test if the results are OK
    //...

    for (int i=0;i<r*c;i++)
    {
        b[i]=i;
    }

    return 0;
}
