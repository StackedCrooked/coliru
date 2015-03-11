#include <iostream>
#include <string>
#include <vector>

using namespace std;

int brPoziva;

int fibo(int x)
{
    brPoziva++;
    if(x == 1)
        return 0;
    if(x == 2)
        return 1;
        
    return fibo(x - 1) + fibo(x - 2);
}

int main()
{
    cout << fibo(12);
}
