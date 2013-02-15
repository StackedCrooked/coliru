#include <iostream>

template <int limit>
void output()
{
    std::cout << limit << std::endl;    
}

int main()
{
    output<100>();
    
    return 0;
}