#include <iostream>
#include <cmath>
using namespace std;

int sumOfSquares(int limit);
int squareOfSum(int limit);

int main()
{
    cout << sumOfSquares(10) << endl;
    cout << squareOfSum(10) << endl;
    cout << squareOfSum(10) - sumOfSquares(10) << endl;
}

int sumOfSquares(int limit)
{
    int sum = 0;
    for(int i = 1; i<=limit; i++)
    {
        sum +=pow(i,2);
    }
    return sum;
}

int squareOfSum(int limit)
{
    int sum = 0, square = 0;
    for(int i = 1; i<=limit; i++)
    {
        sum +=i;
    }
    square = pow(sum,2);
    return square;
}