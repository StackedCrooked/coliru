#include <iostream>
#include <type_traits>
template <std::size_t N>
struct A
{
     template <typename ...Args, typename std::enable_if<N == sizeof...(Args), int>::type = 0>
     A(Args ...) {
         std::cout << __PRETTY_FUNCTION__ << std::endl;
     }

     template <typename ...Args, typename std::enable_if<N+1 == sizeof...(Args), int>::type = 0>
     A(Args ...) {
         std::cout << __PRETTY_FUNCTION__ << std::endl;
     }
};

int main() {
A<3> a(1, 2, 3);
A<3> b(1, 2, 3, 4);
}