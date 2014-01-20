#define NULL nullptr
#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>

long long int fun2(int a, int b, int m)
{
long long int res = 1;
long long int c = a % m;

for (int i = 1; i <= b; i <<= 1)
{
    c = c % m;
    if ((b & i) != 0)
    {
        res = res * c;
        res = res % m;
    }
    c = c * c;
}

return res;
}

int fun(int num, int k)
{
srand((unsigned)time(NULL));

if (num <= 1)
{
    return num * 10;
}

if (num == 2 || num == 3 || num == 5)
{
    return num * 10 + 1;
}

if (num % 2 == 0)
{
    return num * 10;
}

if (num % 3 == 0)
{
    return num * 10;
}

if(num % 5 == 0)
{
    return num * 10;
}

int s = 0;
int s_pow = 1;

while ((s_pow & (num - 1)) == 0)
{
    s  = s + 1;
    s_pow = s_pow << 1;
}

int d = num / s_pow;
bool is_prime;

for (int i = 0; i < k; i++)
{
    int a = (int)((num - 1) * rand() / (RAND_MAX + 1.0)) + 1;
    if(a > INT_MAX)
        a = INT_MAX;
    else if(a < INT_MIN)
        a = INT_MIN;

    if (fun2(a, d, num) != 1)
    {
        is_prime = false;
        for (int r = 0; r <= s - 1; r++)
        {
            if (fun2(a, (1 << r) * d, num) == num - 1)
            {
                is_prime = true;
                break;
            }
        }
        if (!is_prime)
        {
            return num * 10;
        }
    }
}

return num * 10 + 1;
}

int main()
{
    for (int i = 0; i < 100; i++)
        std::cout << fun(i, i) << "\n";
}