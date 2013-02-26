#include <iostream>
#include <type_traits>
 
class A {};
class B : public A {};
class C : public B {};
 
int main() {
    std::cout << std::boolalpha;
    std::cout << "a2b: " << std::is_base_of<A, B>() << '\n';
    std::cout << "b2a: " << std::is_base_of<B, A>() << '\n';
    std::cout << "c2b: " << std::is_base_of<C, B>() << '\n';
    std::cout << "a2c: " << std::is_base_of<A, C>() << '\n';
}