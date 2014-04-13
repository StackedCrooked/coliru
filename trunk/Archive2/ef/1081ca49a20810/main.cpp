template<typename T>
struct has_x {
    typedef char(&yes)[1];
    typedef char(&no)[2];
    
    struct Fallback { char x; };
    struct Derived : T, Fallback { };
    
    template<typename U, U>
    struct Check;
    
    template<typename U>
    static no test(Check<char Fallback::*, &U::x>*);
    
    
    template<typename U>
    static yes test(...);

    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

#include <iostream>

struct A { int x; };
struct B { const char x; };
struct C { void x() volatile ; };
struct D : A { };
struct E {};
struct F : A, B {};  // note that &F::x is ambiguous, but
                     // the test with has_x will still succeed

int main()
{
    std::cout
        << has_x<A>::value
        << has_x<const B>::value
        << has_x<volatile C>::value
        << has_x<const volatile D>::value
        << has_x<E>::value
        << has_x<F>::value;
}
