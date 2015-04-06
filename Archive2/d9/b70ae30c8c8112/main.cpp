#include <iostream>
#include <string>

struct A {
    int a = 0;
    
    // Just some method type chaining (cosmetic)
    A* then = this;
    
    
    A(int a) : a(a) {};
    
    bool test(double other) {
        return this->a == other;  
    };
};




struct MySpecialType {
    int value = 0;
    
    MySpecialType(int v) : value(v) {};
};

// Now we essentially extending `A` to support `MySpecialType`
struct B : public A {
    using A::A;
    
    // This solves the slicing problem
    //B* then = this;
    
    bool test(MySpecialType other) {
        return this->a == other.value;  
    };
};

int main()
{
    //std::cout << "asdf " << B(4).test(MySpecialType(5)) << std::endl;
    // Falling victim to slicing if we don't define a new `then` in `B`
    std::cout << "qwer " << B(4).then->test(MySpecialType(5)) << std::endl;
}


