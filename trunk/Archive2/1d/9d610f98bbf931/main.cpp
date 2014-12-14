#include <iostream>
#include <boost/circular_buffer.hpp>
#include <algorithm>

int main()
{
    const int ONES_REQUIRED = 6 ; // minimum six ones
    const int MAX_WINDOW_SIZE = ONES_REQUIRED*2 - 1 ; // more than 50% ones

    boost::circular_buffer<bool> window(MAX_WINDOW_SIZE) ; // ring buffer
    int nbits = 0 ; // count of total bits seen
    
    std::cout << "input bit stream: " ;
    bool bit ;
    while( std::count( window.begin(), window.end(), true ) < ONES_REQUIRED && std::cin >> bit ) 
    {
        ++nbits ;
        window.push_back(bit) ;
        std::cout << bit << ' ' ;
    }
    
    while( window.front() == false ) window.pop_front() ; // knock off leading zeroes
    
    std::cout << "\nfound sequence: " ;
    for( int bit : window ) std::cout << bit << ' ' ;
    // **** alert: unusual **** : bit count starts at one, not zero
    std::cout << "( bits #" << nbits - window.size() + 1 << " to #" << nbits << " in the input stream)\n" ;
}
