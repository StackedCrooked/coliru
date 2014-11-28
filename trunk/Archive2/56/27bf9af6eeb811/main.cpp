#include <stdio.h> /* printf */
#include <math.h> /* pow, sqrt, exp, erf */
#include <time.h> /* time */
#include <stdlib.h> /* srand, rand */
#define PI 3.14159265358979323846 /* au cas où la constante ne soit pas déjà incluse dans la lib standard */

typedef struct
{
    double mean; /* mu */
    double deviation; /* sigma */
} params_t;

double uniform_rand() /* nombres aléatoire entre 0 et 1 (inclus) */
{
    return rand()/(double)RAND_MAX;
}

double inverse_erf(double x) /* l'inverse de l'error function(erf) */
{
    double result=0.0;
    int steps=0;
    for(;steps<100; ++steps)
    {
        result-=(erf(result)-x)*sqrt(PI)/2*exp(result*result); /* méthode de Newton appliquée au calcul de l'inverse de "erf" */
    }
    return result;
}

double normal_distribution(double x, params_t params); /* f: distribution gaussienne / loi normale*/
double cumulative_normal_distribution(double x, params_t params); /* F: fonction de répartition de la loi normale */
double quantile(double x, params_t params); /* F^-1: l'inverse de la fonction de répatition de la loi normale */
double normal_rand(params_t params) /* Inverse transform sampling */
{
    /* La répartition suit la loi normale d'après: "Caractérisation de la loi par la fonction de répartition" et le "Théorème de la réciproque" */
    return quantile(uniform_rand(),params);
}

#define MAX 100

int main(void)
{
    srand(time(NULL));
    params_t params={1.0,2.0}; // on choisit la moyenne à 1.0 et l'equart type à 2.0
    {
        /* test de l'implémentation */
        double y= uniform_rand(); /* y */
        double x = quantile(y,params); /* F(x)=y */
        printf("y= %.15f; F(%.15f)= %.15f\n", y, x, cumulative_normal_distribution(x, params)); /* on vérifie bien que y= F(x) */
    }
    /* générer les X */
    for(size_t i=0;i<MAX;++i)
    {
        random_variables[i] = normal_rand(params); // on génère un tableau de X et on les affiche au fur et à mesure. Ces nombres aléatoires suivent la loi normale.
        printf("%0.5f\n",random_variables[i]);
    }
    return 0;
}

double normal_distribution(double x, params_t params) /* distribution gaussienne / loi normale*/
{
    double mu = params.mean;
    double sig = params.deviation;
    return 1/(sig*sqrt(2*PI))*exp(-pow(x-mu,2)/(2*pow(sig,2)));
}

double cumulative_normal_distribution(double x, params_t params)
{
    double mu = params.mean;
    double sig = params.deviation;
    return 1/2.0*(1+erf((x-mu)/(sig*sqrt(2))));
}

double quantile(double x, params_t params)
{
    double mu = params.mean;
    double sig = params.deviation;
    return mu+sig*sqrt(2.0)*inverse_erf(2*x-1);
}
