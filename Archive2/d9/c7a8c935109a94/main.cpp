#include <iostream>
#include <string>
#include <vector>

template<typename A, typename B> auto sum(A a,B b) {return (a+b) ;}

int main()
{
    std::cout<<sum(22,6.7) << "\n";
    
}
