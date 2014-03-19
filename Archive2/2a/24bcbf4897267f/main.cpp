#include <random>
#include <vector>
#include <iostream>

struct foo
{
//private:
    unsigned random = distribution(mersenne_generator);    
    static std::random_device seed_generator;
    static unsigned seed;
    static std::mt19937 mersenne_generator;
    static std::uniform_int_distribution<unsigned> distribution;
};

std::random_device foo::seed_generator;
unsigned foo::seed = seed_generator();
std::uniform_int_distribution<unsigned> foo::distribution(0, 10);
std::mt19937 foo::mersenne_generator(foo::seed);

int main()
{
    std::vector<foo> foos(10);
    
    for(auto const& f : foos) {
        std::cout << f.random << ' ';
    }
}
