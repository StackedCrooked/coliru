#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <functional>


int main()
{
    std::random_device rd;
    const size_t test_size = 10000000;
    // Choose a random mean between 1 and 6
    std::mt19937_64 e1(rd());
    std::uniform_real_distribution<double> uniform_dist(-1000.0, 1000.0);
    std::vector<double> d1;
    d1.reserve(test_size);
    std::vector<double> d2;
    d1.reserve(test_size);
    auto random = std::bind(uniform_dist, e1);
    for(size_t i = 0; i < test_size; ++i)
    {
        auto r = random();
        d1.emplace_back(r);
        d2.emplace_back(r);
    }
    
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < test_size; ++i)
    {
        d1[i] *= 0.5;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end -start);
    std::cout << ms.count() << std::endl;
    start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < test_size; ++i)
    {
        d1[i] /= 2.0;
    }
    end = std::chrono::high_resolution_clock::now();
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(end -start);
    std::cout << ms.count() << std::endl;
}
