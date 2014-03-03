#include <chrono>


using namespace std::chrono;


int main()
{    
    // OK
    microseconds() = milliseconds(); 
    
    // ERROR: lossy conversion
    milliseconds() = microseconds();
}
