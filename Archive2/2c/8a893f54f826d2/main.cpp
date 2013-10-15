#include <iostream>

template <int N>
struct Sum {
    enum { value = N + N };    
};
 
int main(){    
    auto y1 = Sum<1>::value;
    auto y2 = Sum<2>::value;
    auto y3 = Sum<3>::value;
    auto y4 = Sum<4>::value;
    
    std::cout << y1 << std::endl;
    std::cout << y2 << std::endl;
    std::cout << y3 << std::endl;
    std::cout << y4 << std::endl;
    
    
    return 0;    
}