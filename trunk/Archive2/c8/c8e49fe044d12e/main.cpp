#include <random>
#include <iostream>

std::uniform_int_distribution<>::param_type
    make_param_type(int min, int max)
{
    return std::uniform_int_distribution<>(min, max).param();
}
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist;
    
    std::cout << dist(gen, make_param_type(0, 10)) << std::endl;
    std::cout << dist(gen, make_param_type(20, 30)) << std::endl;
    std::cout << dist(gen, make_param_type(40, 50)) << std::endl;
}
