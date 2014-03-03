#include <iostream>

struct A ; int bar( A ) ; // bar declared at global namespace scope

struct A
{
    // int foo(A) is defined as a part of the friend declaration
    // 1. there is no previous declaration of int foo(A)
    // 2. the function int foo(a) has global namespace scope
    // 3. the function is implicitly inline
    // 4. however, it is within the lexical scope of class A
    // 5. therefore, it can only be found through ADL (Koenig lookup) unless it is        
    //         injected into the global namespace
    friend int foo( A a ) { return a.v * 2 ; }
    
    // int bar(A) is defined as a part of the friend declaration
    // 1. there is a previous declaration of int bar(A) at global namespace scope
    // 2. the previously declared function is being defined as part of the friend declaration
    // 3. the function is implicitly inline
    friend int bar( A a ) { return a.v * 2 ; }

    int v = 10 ;
};

int main()
{
    A a ;
    
    std::cout << foo(a) << '\n' ; // fine, int ::foo(A) found via ADL
    std::cout << bar(a) << '\n' ; // fine, int ::bar(A) declared at global namespace scope
    
    // std::cout << ::foo(a) << '\n' ; // *** error *** name ::foo not found
    std::cout << ::bar(a) << '\n' ; // fine, ::bar has been declared
    
    // std::cout << A::foo(a) << '\n' ; // *** error *** A does not have a member named foo
}
