#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
    if (num == 0)
        return true;

    int limit = sqrt(num);

    for (int i = 2; i <= limit; i++)
    {
        if (num % i == 0)
            return false;
    }

    return true;
}

int main()
{
    long long sum = 0;
    long long curr = 2;

    while (1)
    {
        if (isPrime(curr))
        {
            if (sum + curr < 1000000)
                sum += curr;
            else
                break;
        }

        curr++;
    }

    for (long long i = sum; !isPrime(sum); sum--) {}

    cout << sum;

    return 0;
}
