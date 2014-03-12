#include <iostream>
#include <iomanip>
using namespace std;

void EvenOdd (int Integer);
void SumDec (int Integer);

int main()
{
    int Integer;
    do
    {
        //cout << "Enter an integer that is between 1 and 100 --> ";
            cin >> Integer;
        
        if(Integer >= 1 && Integer <= 100)
        {
            EvenOdd(Integer);
            SumDec (Integer);
        }
    }
    while (Integer >= 1 && Integer <= 100);
}
void EvenOdd (int Integer)
{
    if((Integer % 2) != 0)
        cout << Integer << " is odd.\n";
    else // if ((Integer % 2) == 0)
        cout << Integer << " is even.\n";
}
void SumDec (int Integer)
{
    int NewInteger, Sum;
    NewInteger = Integer;
    Sum = 0;
    while ( Integer > 0)
    {
        Sum = NewInteger + Sum;
        NewInteger = --Integer;
    }
    cout << "The sum of all the numbers up to and including " << Integer
    << " is " << Sum << endl;
}
