#include <cmath>
#include <cstdio>
using std::fabs;

struct fraction {
    int numerator;
    int denominator;
    int wholeNumber;
};

struct fraction fractionCreate(int numerator, int denominator)
{
    struct fraction result;
    if (denominator == 0)
    {
        result.numerator = 0;
        result.denominator = 0;
    }
    else
    {
        if (numerator*denominator <0)
        {

            int tempNumerator = fabs(numerator);
            int tempDenominator = fabs(denominator);
            int temp = 0;
            while(tempDenominator != 0)
            {
                temp = tempDenominator;
                tempDenominator = tempNumerator%tempDenominator;
                tempNumerator = temp;
            }
            int GCD = tempNumerator;

            numerator = fabs(numerator);
            denominator = fabs(denominator);
            //Num is larger than denom
            if(numerator>=denominator)
            {
                //whole number
                if(numerator%denominator == 0)
                {
                    result.wholeNumber = (numerator/denominator)*-1;
                    result.numerator = 1;
                    result.denominator = 1;
                }
                //mixed number
                else
                {
                    result.wholeNumber = ((numerator - (numerator%denominator)) /denominator)*-1;
                    numerator = (numerator%denominator);
                    if (numerator%GCD ==0 && denominator%GCD ==0)
                    {
                        result.numerator = numerator/GCD;
                        result.denominator= denominator/GCD;
                    }
                    else
                    {
                        result.numerator = numerator;
                        result.denominator = denominator;
                    }
                }
            }

            //simple fraction
            else
            {
                if (numerator%GCD ==0 && denominator%GCD ==0)
                {
                    result.numerator = (numerator/GCD)*-1;
                    result.denominator= denominator/GCD;
                }
                else
                {
                    result.numerator = numerator*-1;
                    result.denominator = denominator;
                }
            }
        }

        if (numerator*denominator > 0)
        {
            int tempNumerator = fabs(numerator);
            int tempDenominator = fabs(denominator);
            int temp = 0;
            while(tempDenominator != 0)
            {
                temp = tempDenominator;
                tempDenominator = tempNumerator%tempDenominator;
                tempNumerator = temp;
            }
            int GCD = tempNumerator;
            numerator = fabs(numerator);
            denominator = fabs(denominator);

            //Num is larger than denom
            if(numerator>=denominator)
            {
                //whole number
                if(numerator%denominator == 0)
                {
                    result.wholeNumber = numerator/denominator;
                    result.numerator = 1;
                    result.denominator = 1;
                }
                //mixed number
                else
                {
                    result.wholeNumber = (numerator - (numerator%denominator)) /denominator;
                    numerator = (numerator%denominator);
                    if (numerator%GCD ==0 && denominator%GCD ==0)
                    {
                        result.numerator = numerator/GCD;
                        result.denominator= denominator/GCD;
                    }
                    else
                    {
                        result.numerator = numerator;
                        result.denominator = denominator;
                    }
                }
            }

            //simple fraction
            else
            {
                if (numerator%GCD ==0 && denominator%GCD ==0)
                {
                    result.numerator = numerator/GCD;
                    result.denominator= denominator/GCD;
                }
                else
                {
                    result.numerator = numerator;
                    result.denominator = denominator;
                }
            }
        }
    }
    return result;
}

void fractionPrint(struct fraction f)
{
    if (f.numerator == 0 && f.denominator == 0)
    {
        printf("Divide by zero!\n");
    }
    else
    {
        // There IS a whole number
        if (f.wholeNumber !=0)
        {
            int tempNumerator;
            if (f.numerator <0)
            {
                tempNumerator = f.numerator *-1;
            }
            //ONLY whole number
            if (tempNumerator == 1 && f.denominator ==1 )
            {
                printf("%d\n", f.wholeNumber);
            }
            //Mixed number
            else
            {
                printf("%d %d/%d\n", f.wholeNumber, f.numerator, f.denominator);
            }
        }
        //fraction only
        else
        {
            printf("%d/%d\n", f.numerator, f.denominator);
        }
    }

}

int main (void)
{
    struct fraction a, b, c, d, r, bad;

    a = fractionCreate (-5, -6);
    fractionPrint(a);
    b = fractionCreate (-10, 2);
    fractionPrint(b);
    c = fractionCreate (56, -160);
    fractionPrint(c);
    d = fractionCreate (-35, 150);
    fractionPrint(d);
    bad = fractionCreate (8, 0);
    fractionPrint(bad);


    return 0;
}