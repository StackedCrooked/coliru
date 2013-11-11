#include <iostream>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <numeric>
#include <algorithm>
#include <iterator>

bool UseAllDigits( size_t number ) {
    std::array<bool,10> found;
    found.fill( false );
    
    size_t digits = 0;
    for ( ; number ; number /= 10 ) {
        auto frac = number % 10;
        if ( found[frac] == false ) {
            found[frac] = true;
            ++digits;
        }
    }
    return digits == 10;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(10000000000, std::numeric_limits<size_t>::max());
    
    std::vector<size_t> numbers;
    
    size_t const num = 1000000;
    numbers.reserve( num );
    
    std::generate_n( std::back_inserter( numbers ), num, [&] { return dis(gen); } );
        
    using hrc = std::chrono::high_resolution_clock;
        
    size_t count = 0;
    auto t0 = hrc::now();
    for ( auto n : numbers )
        count += UseAllDigits( n );
    auto t1 = hrc::now();
    
    std::cout << count << " numbers of "<< num<< " have all the digit, tested in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()<<"ms"<<std::endl;
    
    return 0;
}
