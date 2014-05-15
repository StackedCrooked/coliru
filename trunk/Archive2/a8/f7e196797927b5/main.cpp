#include <type_traits>
#include <iostream>


namespace NS_A {
    struct A {};
    
    int g(std::common_type<int>, A) {
        return 1;
    }
    
    
    template<class T>
    T g(std::common_type<T>, A) {
        return static_cast<T>(-1);
    }

}

namespace NS_B {
    struct B {};
    
    int g(std::common_type<int>, B) {
        return 2;
    }
    
    template<class T>
    T g(std::common_type<T>, B) {
        return static_cast<T>(-2); 
    }
}

void f(int a) {
    std::cout << "int :" << a << std::endl;
}

void f(double a) {
    std::cout << " double :" << a << std::endl;
}


int main() {
    f(g(std::common_type<int>(), NS_A::A()));
    f(g(std::common_type<double>(), NS_B::B()));
    f(g(std::common_type<int>(), NS_A::A()));
    f(g(std::common_type<double>(), NS_B::B()));
    
    return 0;
}