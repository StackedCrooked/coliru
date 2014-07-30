#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{

    unsigned long long i;
    int div=0,j;
    int num=0;
    for(i=1;div != 500;)
    {
        num += i;
        cout << num << "'s divisors are:\t";
        for(j=1;j<=i;j++)
        {
            if (num%j == 0)
            {
                cout << j << ' ';
                ++div;
            }
        }
        cout << '\n';
        if(div == 500)
        {
            cout << num;
            exit(0);
        }
        else
            div=0;
        i++;
    }
    return 0;
}