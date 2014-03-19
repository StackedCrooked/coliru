#include <iostream>
#include <chrono>
  
int main()
{
    using namespace std::chrono;
    
    // define the napatech timestamp type
    typedef duration<int64_t, std::ratio<1, 100000000>> napatech_timestamp; // units of 10 nanoseconds

    napatech_timestamp napatech(1234);
    
    // implicit conversion allowed for widening conversion
    nanoseconds ns = napatech; 
    
    // narrowing conversion requires duration_cast
    microseconds us = duration_cast<microseconds>(napatech); 
    
    // check the result
    std::cout << napatech.count() << " napatech units == " << ns.count() << " nanoseconds == " << us.count() << " microseconds " << std::endl;    
}
