#include <type_traits>
#include <iostream>
     
struct ParameterTypeA {};
struct ParameterTypeB {};
     
enum class MyCases {
    CASE1,
    CASE2
};

template<enum MyCases U>
class MyClass
{
public:
    MyClass() { }
    ~MyClass() { }
    
    template<enum MyCases T = U>
    void myFunction(ParameterTypeA a, typename std::enable_if<T == MyCases::CASE1, void>::type* = nullptr) {
        std::cout << "A" << std::endl;
    }
    
    template<enum MyCases T = U>
    void myFunction(ParameterTypeB b, typename std::enable_if<T == MyCases::CASE2, void>::type* = nullptr) {
        std::cout << "B" << std::endl;
    }
};

int main() {
    MyClass<MyCases::CASE1> m1;
    m1.myFunction(ParameterTypeA{});
    MyClass<MyCases::CASE2> m2;
    m2.myFunction(ParameterTypeB{});
    return 0;
}