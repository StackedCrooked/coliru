#include <iostream>
#include <string>

namespace FooSpace {
    template<typename T>
    struct A {
        int a = 0;
        
        A* then = this;
        
        A(int a) : a(a) {};
        
        
        bool test(double other) {
            return this->a == other;  
        };
    };
};





struct MySpecialType {
    int value = 0;
    
    MySpecialType(int v) : value(v) {};
};

// Now we essentially extending `A` to support `MySpecialType`
template<typename T>
struct B : public FooSpace::A<T> {
    using FooSpace::A<T>::A;
    
    //B* then = this;
    
    bool test(MySpecialType other) {
        return this->a == other.value;  
    };
};

int main()
{
    //std::cout << "asdf " << B<int>(4).test(MySpecialType(5)) << std::endl;
    // Falling victim to method slicing if we don't define a new `then` in `B`
    std::cout << "qwer " << B<int>(4).then->test(MySpecialType(5)) << std::endl;
}


