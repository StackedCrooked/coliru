#include <iostream>
#include <vector>
#include <string>

#include <thread>
#include <future>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/lexical_cast.hpp>

using boost::multiprecision::cpp_int;
using boost::multiprecision::uint128_t;

/// Multithreaded factorial helper.
///
/// @param n The calculation the helper is working towards (i.e. n!)
/// @param tc The number of threads.
/// @param tid The ID of this thread, in range [0,tc)
/// @return The value for the helper.
cpp_int mt_fact(uint128_t n, uint128_t tc, uint128_t tid) {
    cpp_int x = 1;
    for (auto i = tid+1; i <= n; i += tc)
        x *= i;
    return x;
}

/// Usage helper.
///
/// @param name The name of the program.
void print_usage(char* name) {
    std::cerr << "Usage: " << name << " [-c X] n\n"
              << "  -c    Set the thread count to X (default 4)\n"
              << "  n     The value to calculate (i.e. n!)" << std::endl;
}

int main(int argc, char* argv[]) {
    uint128_t tc = 4;
    uint128_t n;
    
    if (argc != 2 && argc != 4) {
        print_usage(argv[0]);
        return 1;
    }
    
    try {
        if (std::string(argv[1]) == "-c") {
            tc = boost::lexical_cast<uint128_t>(argv[2]);
            n  = boost::lexical_cast<uint128_t>(argv[3]);
        } else {
            n  = boost::lexical_cast<uint128_t>(argv[1]);
        }
    } catch (boost::bad_lexical_cast& blc) {
        std::cerr << "Exception Caught: " << blc.what() << std::endl;
        print_usage(argv[0]);
        return 1;
    }
    
    std::clog << "Using tc=" << tc << " and n=" << n << std::endl;
    
    std::vector<std::future<cpp_int>> futures;
    for (uint128_t i = 0; i < tc; ++i)
        futures.emplace_back(std::async(std::launch::async, [n,tc,i](){ return mt_fact(n, tc, i); }));
    
    for (auto&& x : futures)
        x.wait();
    
    cpp_int result = 1;
    for (auto&& x : futures)
        result *= x.get();
    
    std::cout << result << std::endl;
    
    return 0;
}