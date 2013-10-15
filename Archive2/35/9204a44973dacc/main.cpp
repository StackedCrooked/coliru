#include <iostream>
#include <chrono>
using namespace std;

const unsigned long long N = 1000000000ULL;  // constexptr is tested, no effect

unsigned long long s(unsigned long long n)
{
    unsigned long long s = 0;

    for (unsigned long long i = 0; i < n; i++)
        s += i;

    return s;
}

int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();

    auto x = s(N);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

    cout << "Result: " << x << " -- time (ms):" << t/0.1e7 << endl;
}