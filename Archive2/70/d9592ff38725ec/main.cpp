#include <iostream>

template <typename... Args>
class VariadicTemplate {
public:
    static const unsigned int theSize = sizeof...(Args);  
};

template <typename T1, typename T2, typename T3>
using intVariadic = VariadicTemplate<int, T1, T2, T3>;

int main(){
    intVariadic<int,int,int> container;
    std::cout << container.theSize << std::endl;
    
    return 0;    
}