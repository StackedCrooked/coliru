#include <functional>
#include <iostream>
#include <utility>

int main()
{
    typedef std::pair<int, int> P;
    
    P pair = std::make_pair(1, 2);
    
    int& first  = std::bind(&P::first, &pair)();
    int& second = std::mem_fn(&P::second)(&pair);
    
    std::cout << first << ", " << second << std::endl;
}