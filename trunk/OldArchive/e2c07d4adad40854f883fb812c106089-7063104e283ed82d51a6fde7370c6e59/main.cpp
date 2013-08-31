#include <cassert>
#include <iostream>
#include <vector>
#include <stdint.h>


// getting the n-th Fibonnacci number
// 0 1 1 2 3 5 ...
uint64_t get_fib(unsigned n)
{
    static std::vector<uint64_t> cache = { 0, 1 };
    if (n < cache.size())
    {
        return cache[n];
    }
    auto result = get_fib(n - 2) + get_fib(n - 1);
    
    if (n == cache.size())
    {
        cache.push_back(result);
    }
    return result;
}


int main()
{
    std::cout << "begin" << std::endl;
    for (int i = 0; i != 50; ++i)
    {
        std::cout << get_fib(i) << std::endl;
    }
}