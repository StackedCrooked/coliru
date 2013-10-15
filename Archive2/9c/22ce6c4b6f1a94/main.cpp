#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();

    unsigned long long s = 0;
    for (unsigned long long i = 0; i < 1000000000ULL; i++)
        s += i;

    auto t2 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

    cout << "Result: " << s << " -- time (ms):" << t/0.1e7 << endl;
#if defined __linux__ and __x86_64__ and __GNUG__
    cout << "g++ " << __VERSION__ << ", Linux 64 bit" << endl;
#endif    
}
