#include <functional>
#include <iostream>

struct Sum
{    
    template<typename T>
    void operator()(T a, T b, std::enable_if(sizeof(T) <= sizeof(long))
    {
        return a + b;
    }
    
    template<typename T>
    void operator()(const T & a, const T & b, std::enable_if(sizeof(T) > sizeof(long))
    {
        return a + b;
    }
}


int main()
{    
    std::vector<unsigned> vec(1000);
    unsigned i = 0;
    for (auto & n : vec) { n += ++i; };
    std::cout << std::accumulate(vec.begin(), vec.end(), Sum()) << std::endl;
}
