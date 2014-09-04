#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main()
{
    typedef high_resolution_clock::time_point TimePoint;
    
    ///////////////////////////////////////////////////
    TimePoint start = high_resolution_clock::now();
    
    for(int i = 0; i < 100; ++i)
        cout << "Hello World!\n";
        
    TimePoint end = high_resolution_clock::now();
    ///////////////////////////////////////////////////
    
    cout << "It took: " << (duration_cast<nanoseconds>(end - start)).count() << " nanoseconds to print 100 hello worlds";
}