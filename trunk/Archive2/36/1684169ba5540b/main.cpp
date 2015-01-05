#include <functional>
#include <iostream>

int main()
{
    typedef std::pair<int, int> P;
    P pair(1, 2);
    
    int& first  = std::bind(&P::first, &pair)();
    int& second = std::mem_fn(&P::second)(&pair);
    
    std::cout << first << ", " << second << std::endl;
}