#include <boost/optional.hpp>
#include <chrono>
#include <vector>
#include <random>

int main()
{
    using T = boost::optional<int>;
    constexpr auto size = 1000*1000;
    
    auto v = std::vector<T>(size);
    
    std::random_device rd;
    std::uniform_int_distribution<> dist;
    std::mt19937 gen;
    auto const rand = [&dist, &gen]{ return dist(gen); };
    
    for(auto& e : v)
    {
        e = rand();
    }
    
    auto const start = std::chrono::high_resolution_clock::now();
    std::sort(begin(v), end(v));
    auto const stop = std::chrono::high_resolution_clock::now();
    
    std::cout << "result: "<<v[ std::uniform_int_distribution<>(0, size)(gen) ]<<"\n";
    std::cout << "duration: "<<std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms\n";
}