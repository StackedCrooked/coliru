#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h> 
#include <sys/time.h>
using namespace std;
double getTimeElapsed(struct timeval end, struct timeval start)
{
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.00;
}
double max(double a,double b)
{
    if (a>b) return a;
    else return b;
}
int main(int argc, char *argv[])
{
    struct timeval t0, t1; 
    double htime;
    double **laplace,prev,qa=0,accu=10e-4;
    int i,j,rowcol,step=0;
    
    rowcol = 100;
    accu = 1E-05;
    laplace = new double *[rowcol+1];
    for (i=0;i<=rowcol;i++) 
        laplace[i]=new double [rowcol+1];
    #pragma omp parallel for //MP init
    for (i=0;i<=rowcol;i++)
        for (j=0;j<=rowcol;j++)
        {
            if (j==0) laplace[i][j] = 1.0;
            else laplace[i][j] = 0.0;
        }
    gettimeofday(&t0, NULL);
    while(1)
    {
        #pragma omp parallel for shared(rowcol,laplace,prev) reduction (max:qa) //mp calculation
        for(i=1;i<=rowcol-1;i++)
            for(j=1;j<=rowcol-1;j++)
            {
                prev=laplace[i][j];
                laplace[i][j]=0.25*(laplace[i+1][j]+laplace[i-1][j]+laplace[i][j+1]+laplace[i][j-1]);
                qa=max(qa,abs(laplace[i][j]-prev));
            }
        if (qa < accu)
        {
            gettimeofday(&t1, NULL);
            htime=getTimeElapsed(t1,t0);
            cout << "Done!" << endl << "Time used: " << htime << endl;
            for (i=0;i<=rowcol;i++) delete [] laplace[i];
            delete [] laplace;
            exit(0);
        }
        else 
        {
            step++;
            if (step%80==0) cout << "Iteration = " << step << " ,  Error= " << qa << endl;
            qa=0;
        }
    }
   
    return 0;
}