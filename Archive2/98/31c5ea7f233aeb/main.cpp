#include <iostream>
#include <ctime>
#include <ctime>

int main()
{
    const auto max_secs = std::numeric_limits<std::clock_t>::max() / double( CLOCKS_PER_SEC ) ;
    
    std::cout << "the maximum number of sconds that can be reported: " 
              << std::fixed << max_secs << " (" << max_secs / 3600 << " hours)\n" ;
}

