#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
#include <chrono>

using hrclock = std::chrono::high_resolution_clock;

int main()
{
    std::random_device rd;
    std::default_random_engine rde(rd());
    std::uniform_int_distribution<int> uid(0, 25);


    #define N 1000000000ull

    {
        auto start = hrclock::now();
        std::cout << "String.\n";
        std::string s;
        s.resize(N);
        std::generate_n(s.begin(), N, 
                [&]() { return (char)(uid(rde) + 65); });
        std::cout << "String: " << std::chrono::duration_cast<std::chrono::milliseconds>(hrclock::now() - start).count() << "ms\n";
    }

    {
        auto start = hrclock::now();
        std::cout << "Vector.\n";
        std::vector<char> v;
        v.resize(N);
        std::generate_n(v.begin(), N, 
                [&]() { return (char)(uid(rde) + 65); });
        std::cout << "Vector: " << std::chrono::duration_cast<std::chrono::milliseconds>(hrclock::now() - start).count() << "ms\n";
    }

    return 0;
}
