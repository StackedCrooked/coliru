#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define M 100

double compute_error(double solution[][M + 2], double u[][M + 2], const int m, const int iters);
void sor(double unew[][M + 2], double uold[][M + 2], double solution[][M + 2], const double omega, const double tol, const int m, int *iters);

int main(int argc, char ** argv)
{

/*  
    Solution of Laplace's Equation.
    ==============================
    ! ***
    ! ***  Uxx + Uyy = 0
    ! ***  0 <= x <= pi, 0 <= y <= pi
    ! ***  U(x,pi) = sin(x), U(x,0) = U(0,y) = U(pi,y) = 0
    ! ***
    ! ***  then U(x,y) = (sinh(y)*sin(x)) / sinh(pi)
    ! ***
    ! ***  Should converge with
    ! ***            tol = 0.001 and M = 20  in  42 iterations.
    ! ***   and with tol = 0.001 and M = 100 in 198 iterations. 

*/

    double pi;

    double unew[M + 2][M + 2];
    double solution[M + 2][M + 2];

    double uold[M + 2][M + 2];

    double omega, tol, h;

    int i, j, iters;

    // Initialization
    for(i = 0; i <= M + 1; ++i)
    {
        for(j = 0; j <= M + 1; ++j)
        {
            unew[i][j] = 0;
            uold[i][j] = 0;
            solution[i][j] = 0;
        }
    }

    pi = 4.0 * atan(1.0);

    h = pi / (M + 1);

    for(i = 0; i <= M + 1; ++i)
    {
        uold[i][M + 1] = sin(i * h);
    }

    for(i = 0; i <= M + 1; ++i)
    {
        for(j = 0; j <= M; ++j)
        {
            uold[i][j] = j * h * uold[i][M + 1];
        }
    }

    for(i = 0; i <= M + 1; ++i)
    {
        for(j = 0; j <= M + 1; ++j)
        {
            solution[i][j] = sinh(j * h) * sin(i * h) / sinh(pi);
        }
    }

    omega = 2.0 / ( 1.0 + sin(pi / (M + 1)) );
    printf("omega = %.10f\n", omega);
    tol = 0.001;

    sor(unew, uold, solution, omega, tol, M, &iters);

    printf(" \n");
    printf(" Omega = %f\n", omega);
    printf(" It took %d iterations.\n", iters);

    return 0;
}

double compute_error(double solution[][M + 2], double u[][M + 2], const int m, const int iters)
{
    double error = 0.0;
    int i, j;

    for(j = 1; j <= m; ++j)
    {
        for(i = 1; i <= m; ++i)
        {

            if(error >= fabs(solution[i][j] - u[i][j]))
                error = error;
            else
                error = fabs(solution[i][j] - u[i][j]);

        }
    }

    printf("On iteration %d error = %f\n", iters, error);

    return error;
}

void sor(double unew[][M + 2], double uold[][M + 2], double solution[][M + 2], const double omega, const double tol, const int m, int *iters)
{
    double error;
    int i, j;

    for(i = 0; i <= m + 1; ++i)
    {
        unew[i][m + 1] = uold[i][m + 1];
        unew[m + 1][i] = uold[m + 1][i];
        unew[i][0] = uold[i][0];
        unew[0][i] = uold[0][i];
    }

    *iters = 0;
    error = compute_error(solution, uold, m, *iters);

    while(error >= tol)
    {


        for(j = 1; j <= m; ++j)
        {
            for(i = 1; i <= m; ++i)
            { 
                unew[i][j] = uold[i][j] + 0.25 * omega *
                                 (unew[i - 1][j] + unew[i][j - 1] +
                                 uold[i + 1][j] + uold[i][j + 1] -
                                 4.0 * uold[i][j]);     

            }
        }

        for(j = 1; j <= m; ++j)
        {
            for(i = 1; i <= m; ++i)
            { 
                uold[i][j] = unew[i][j];
            }
        }

        *iters += 1;

        if(*iters % 2 == 0)
        {
            error = compute_error(solution, uold, m, *iters);
        }
    }
}