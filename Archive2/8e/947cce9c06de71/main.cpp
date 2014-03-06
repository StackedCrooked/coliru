#include <iostream>
#include <vector>

template<typename T>                    
T tsum(std::vector<T> d)
{              
    T s = 0;                       
    for(auto x : d) { s += x; }
    return s;                           
}

int main()
{
    std::vector<int> f(1,5);
    tsum(f);
    
    std::vector<double> v(2, 6);
    tsum(v);
    
    return 0;
}