#include <iostream>
#include <random>
#include <chrono>
#include <functional>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for //num_threads(2)
    for (int i = 0; i < 100; i++) {
        ::std::mt19937 twister;
        ::std::uniform_real_distribution<float> dist(-1.0F, 1.0F);
	    auto random = ::std::bind(dist, twister);
        float trash = 0;
        for (int j = 0; j < 1000000; j++)
            trash += random();
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop - start;
    std::cout << elapsed_seconds.count() << '\n';
}
