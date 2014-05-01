#include <iostream>
#include <typeinfo>

class A { public: virtual ~A() = default ; };
class B : public A{};
class C : public A{};

void func( A* a )
{
    if( a != nullptr )
    {
        std::cout << "dynamic type of the object pointed to is: " ;
        
        // http://en.cppreference.com/w/cpp/language/typeid
        const std::type_info& type_info = typeid(*a) ; // typeid on reference to a polymorphic type

        if( type_info == typeid(A) ) std::cout << "A\n" ;
        else if( type_info == typeid(B) ) std::cout << "B\n" ;
        else if( type_info == typeid(C) ) std::cout << "C\n" ;
        else std::cout << "an unknown class derrived from A\n" ;
    }
}

int main()
{
    A a ; A* pa = &a ; func(pa) ; // A
    B b ; pa = &b ; func(pa) ; // B
    C c ; pa = &c ; func(pa) ; // C
    struct D : A {} d ; pa = &d ; func(pa) ; // an unknown class derrived from A
}
