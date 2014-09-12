#include <iostream>
using namespace std;
int main()
{
    int number = 36;

    if (number < 1)
    {
        cout << 0;
    }
    else if (number == 1)
    {
        cout << number;
    }

    for (int i=2; i <= number; i++)
    {

         while (number % i == 0)
         {
             number /= i;
             cout << i << (i + 1 <= number ? ", " : "");
         }

    }
    cout << endl;
    return 0;
}
