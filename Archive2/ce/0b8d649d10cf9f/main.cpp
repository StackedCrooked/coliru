#include <iostream>
#include <chrono>
 
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using std::cout;
 
int main()
{
    steady_clock::time_point start = steady_clock::now();
    cout << "Hello World\n";
    steady_clock::time_point end = steady_clock::now();
    cout << "Printing took "
         // duration_cast is required to avoid accidentally losing precision.
         << duration_cast<microseconds>(end - start).count()
         << "us.\n";
}