#include <type_traits>
#include <iostream>
#include <ios>

struct Base
{
    // dummy template parameter...
    template<class U, class _ = void> struct Inner: std::true_type {};
    
    // ... to allow in-class partial specialization
    template<class _> struct Inner<char, _>: std::false_type {};
};

struct Derived
:
    Base
{
    // cannot partially specialize Inner inside Derived...
    //template<class _>
    //struct Inner<int, _>: std::false_type {};
};

// ... but specializing Derived::Inner at namespace scope, also specializes it for Base::Inner
template<class _> struct Derived::Inner<int, _>: std::false_type {};

int main()
{
    std::cout << std::boolalpha << Base::Inner<float>::value << "\n";    
    std::cout << std::boolalpha << Derived::Inner<float>::value << "\n";    

    std::cout << std::boolalpha << Base::Inner<char>::value << "\n";    
    std::cout << std::boolalpha << Derived::Inner<char>::value << "\n";    
    
    std::cout << std::boolalpha << Base::Inner<int>::value << "\n";      // huh???
    std::cout << std::boolalpha << Derived::Inner<int>::value << "\n";   // OK 
}
