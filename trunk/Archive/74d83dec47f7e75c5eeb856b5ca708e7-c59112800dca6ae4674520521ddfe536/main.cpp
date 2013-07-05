#include <iostream>
#include <type_traits>
#include <array>
#include <utility>
#include <tuple>

template <class Crtp, class... Types>
struct Base
{
    Base(const Types&... rhs) : 
        data(std::forward_as_tuple(rhs...)) {;}
    std::tuple<Types...> data;
};

struct Derived 
: public Base<Derived, std::array<double, 3>>
{
    template <class... Args> 
    Derived(Args&&... args) :
        Base<Derived, std::array<double, 3>>(std::forward<Args>(args)...) {;}
};

int main(int argc, char* argv[])
{
    Derived a(std::array<double, 3>({{1, 2, 3}})); 
    Derived b(a);
    Derived c(std::array<double, 3>()); 
    // Derived d(c); // Not working : why ?
    
    return 0;
}
