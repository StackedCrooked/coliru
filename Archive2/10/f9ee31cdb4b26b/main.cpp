#include <iostream>
#include <tuple>
#include <stdexcept>

const class {
public:
    virtual void test() = 0;
} constClass = {};

template <typename... Args, typename T>
class VariadicTemplate : public constClass {
public:
    static const unsigned int theSize = sizeof...(Args);
    void test(){}
};

template <typename T1, typename T2, typename T3>
using intVariadic = VariadicTemplate<int, T1, T2, T3>;


int main(){
    intVariadic<int,int,int> container;
    std::cout << container.theSize;
    
    return 0;    
}