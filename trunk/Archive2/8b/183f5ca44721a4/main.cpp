#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ratio>
using namespace std;

class VigTime
{
private:
    typedef ratio<1,3600> hours;
    typedef ratio<1,60> minutes;  
    typedef ratio<1,1> seconds;
    typedef ratio<1,1000> milliseconds;
    typedef ratio<1,1000000> microseconds;
    typedef ratio<1,1000000000> nanoseconds;
public:
    chrono::duration<double,hours> HRS;                  // 60 Minutes = 3600 Seconds
    chrono::duration<double,minutes> MINS;               // 60 Seconds 
    chrono::duration<double,seconds> SEC;                // Standard
    chrono::duration<double,milliseconds> MS;            // 1/1000       Second
    chrono::duration<double,microseconds> US;            // 1/1000000    Second
    chrono::duration<double,nanoseconds> NS;             // 1/1000000000 Second
};
int main()
{
    chrono::high_resolution_clock::time_point Epoch;
}
