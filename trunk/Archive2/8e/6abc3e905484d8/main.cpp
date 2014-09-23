#include <iostream>

int main()
{
    int i = 0;
    auto gen_lam = [=]() mutable -> int {return ++i;};
    std::cout << gen_lam() << std::endl;
    
    decltype(gen_lam) gen_lam2;
    
    std::cout << gen_lam2() << std::endl;
    
    return 0;
}