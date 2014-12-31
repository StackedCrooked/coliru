#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <limits>

#include <cmath>
#include <cstdlib>

int
main()
{
    using G = long double;
    G const one = G(1);
    std::mt19937_64 random_(static_cast< typename std::mt19937_64::result_type >(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution< G > zero_to_one_; // uniform [0;1) ditribution
    std::uniform_int_distribution< int > uniform_int_(std::numeric_limits< G >::min_exponent - 1, std::numeric_limits< G >::max_exponent - 1);
    std::cout.precision(std::numeric_limits< G >::digits10);
    for (std::size_t i = 0; i < 100; ++i) {
        std::cout << std::scalbn(one + zero_to_one_(random_), uniform_int_(random_)) << std::endl;
    }
    return EXIT_SUCCESS;
}
