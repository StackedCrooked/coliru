#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>


struct Sum
{    
    template<typename T>
    T operator()(T a, T b, typename std::enable_if<(sizeof(T) <= sizeof(void*))>::type * = 0) const
    {
        return a + b;
    }
    
    template<typename T>
    T operator()(const T & a, const T & b, typename std::enable_if<(sizeof(T) > sizeof(void*))>::type * = 0) const
    {
        return a + b;
    }
};


int main()
{    
    std::vector<unsigned> vec(500);
    unsigned i = 0;
    for (auto & n : vec) { n += ++i; };
    std::cout << std::accumulate(vec.begin(), vec.end(), 0u, Sum()) << std::endl;
}
