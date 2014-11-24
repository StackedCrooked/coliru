#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


double taylor_tan(double x, unsigned int n) ///kde x udává úhel a n rozvoj polynomu (počet členů)
{
    double numerator[15] = {0, 1, 1, 2, 17, 62, 1382, 21844, 929569, 6404582, 443861162, 18888466084, 113927491862, 58870668456604};
    double denominator[15] = {0, 1, 3, 15, 315, 2835, 155925, 6081075, 638512875, 10854718875, 1856156927625, 194896477400625, 49308808782358125, 3698160658676859375};
    double tTan = 0;
    double xExp = x;
    int i;
    for (i = 1; i <= 13; i++){

      tTan = tTan + (numerator[i]*xExp)/(denominator[i]);
      xExp = xExp*x*x;
    }
    return tTan;
}


double cfrac_tan(double x, unsigned int n) ///kde x udává úhel a n rozvoj zřetězeného zlomku
{
    int i;
    int iamount = 0;
    double cTan;
    double xPrevious = 0;
    for(i = n; i > 0; i--){
        cTan = 1 / (((2*i-1) / x) - xPrevious);
        xPrevious = cTan;
        iamount++;
    }
    return cTan;
}


int main(int argc, char *argv[])
{

    if (argc > 3) {
        if (!strcmp(argv[1],"--help")) {
            printf("\n\t\tHELP.\n");
            printf("'--tan A N M' - srovna presnosti vypoctu tangens uhlu A (v radianech) mezi volanim tan \n");
            printf("z matematicke knihovny, a vypoctu tangens pomoci Taylorova polynomu a zretezeneho zlomku.\n");
            printf("Argumenty N a M udavaji, ve kterych iteracich iteracniho vypoctuma srovnani probihat. 0 < N <= M < 14\n");
            printf("\n\n\n");
        }
        else if ((argc >= 2) && (!strcmp(argv[1],"--tan"))) {
            double x = atof(argv[2]);

            printf("i "); ///počet iterací iteračního výpočtu
            printf("%10e ", tan(x)); ///výsledek z funkce tan matematické knihovny
            printf("%10e ", taylor_tan(x, 10)); ///výsledek z funkce taylor_tan
            printf("%10e\n", cfrac_tan(x, 10)); ///výsledek z funkce cfrac_tan

        }
    else {
        printf("You didn't enter the argument, use --help");
    }

    }

    printf("\n\n\n");
    printf("%10e ", tan(1.024)); ///výsledek z funkce tan matematické knihovny
    printf("%10e ", taylor_tan(1.024, 10)); ///
    printf("%10e\n", cfrac_tan(1.024, 10)); ///

    return 0;
}
