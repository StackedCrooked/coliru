#include <iostream>
#include <sstream>
#include <typeinfo>

class B {};

int main() {
    std::stringstream ss;
    B b;
    int v;
    
    std::cout << typeid(decltype(ss>>v )).name() << "\n" ;
    std::cout << typeid(decltype(ss<<1 )).name() << "\n" ;
    std::cout << typeid(decltype(std::declval<std::stringstream>()>>v )).name() << "\n" ;
    std::cout << typeid(decltype(std::declval<std::stringstream>()<<1 )).name() << "\n" ;
    
    //std::cout << typeid(decltype(ss>>b )).name() << "\n" ; // do not compile
    //std::cout << typeid(decltype(ss<<b )).name() << "\n" ; // do not compile
    std::cout << typeid(decltype(std::declval<std::stringstream>()>>b )).name() << "\n" ; // should not compile but succeed
    std::cout << typeid(decltype(std::declval<std::stringstream>()<<b )).name() << "\n" ; // should not compile but succeed
}