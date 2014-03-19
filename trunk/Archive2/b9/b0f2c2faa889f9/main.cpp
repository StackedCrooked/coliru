#include <iostream>
#include <chrono>
#include <string>


typedef std::chrono::duration<int64_t, std::ratio<1, 1000000>> microseconds; // identical to std::chrono::microseconds
typedef std::chrono::duration<int64_t, std::ratio<1, 1000000000>> nanoseconds; // identical to std::chrono::nanoseconds
typedef std::chrono::duration<int64_t, std::ratio<1, 100000000>> napatech_timestamp; // units of 10 nanoseconds
  
  
int main()
{
    napatech_timestamp napatech(1234);
    nanoseconds ns = napatech; // implicit conversion allowed for widening conversion
    microseconds us = std::chrono::duration_cast<microseconds>(napatech); // narrowing conversion requires duration_cast
    
    std::cout
        << napatech.count() << " napatech units => "
        << ns.count() << " nanoseconds or "
        << us.count() << " microseconds "
        << std::endl;
}
