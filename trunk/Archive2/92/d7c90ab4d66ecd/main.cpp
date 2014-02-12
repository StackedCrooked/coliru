#include <chrono>
#include <iostream>

using namespace std;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::chrono::steady_clock;

int main()
{
    int times = 10;
    steady_clock::time_point t1 = steady_clock::now();
    for (int i = 0; i < times; i++)
    {
        
    }
    steady_clock::time_point t2 = steady_clock::now();
    cout << (float)duration_cast<nanoseconds>(t2 - t1).count()/times << "     ";
}