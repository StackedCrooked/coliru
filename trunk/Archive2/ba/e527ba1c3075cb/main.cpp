#include <type_traits>
#include <iostream>
     
struct ParameterTypeA {};
struct ParameterTypeB {};
     
template<typename U>
class MyClass
{
public:
    MyClass() { }
    ~MyClass() { }
    
    template<typename T = U>
    void myFunction(ParameterTypeA a, typename std::enable_if<std::is_same<ParameterTypeA, T>::value, void>::type* = nullptr) {
        std::cout << "A" << std::endl;
    }
    
    template<typename T = U>
    void myFunction(ParameterTypeB b, typename std::enable_if<std::is_same<ParameterTypeB, T>::value, void>::type* = nullptr) {
        std::cout << "B" << std::endl;
    }
};

int main() {
    MyClass<ParameterTypeA> m1;
    
    m1.myFunction(ParameterTypeA{});
    
    MyClass<ParameterTypeB> m2;
    
    m2.myFunction(ParameterTypeB{});
    return 0;
}