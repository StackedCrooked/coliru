#include <type_traits>
#include <iostream>

template<class T>
using ret_type = std::common_type<T>;


namespace NS_A {
    struct A {};
    
    int g(ret_type<int>, A) {
        return 1;
    }
    
    
    template<class T>
    T g(ret_type<T>, A) {
        return static_cast<T>(-1);
    }

}

namespace NS_B {
    struct B {};
    
    int g(ret_type<int>, B) {
        return 2;
    }
    
    template<class T>
    T g(ret_type<T>, B) {
        return static_cast<T>(-2); 
    }
}

void f(int a) {
    std::cout << "int    (overload of g)        : " << a << std::endl;
}

void f(double a) {
    std::cout << "double (generic version of g) : " << a << std::endl;
}


int main() {
    f(g(ret_type<int>(), NS_A::A()));
    f(g(ret_type<int>(), NS_B::B()));
    f(g(ret_type<double>(), NS_A::A()));
    f(g(ret_type<double>(), NS_B::B()));

    std::cout 
        << std::endl
        << "float with conversation to double: " << std::endl;
    f(g(ret_type<float>(), NS_A::A()));
    f(g(ret_type<float>(), NS_B::B()));
    
    return 0;
}