#include <iostream>
#include <vector>

using namespace std;


std::vector<int> fibo(int n)
{
    std::vector<int> w_fibo;
    w_fibo.reserve(n);
    
    if (n >= 0)
        w_fibo[0] = 1;
    if (n >= 1)
        w_fibo[1] = 1;

    for (int i = 1; i < n; i++)
        w_fibo[i + 1] = w_fibo[i] + w_fibo[i - 1];

    return w_fibo;
}

int main()
{    
    int n = 10;
    std::vector<int> fibonacci = fibo(n);
    for (int i = 0; i<n; i++)
        cout << fibonacci[i] << " ";
}

