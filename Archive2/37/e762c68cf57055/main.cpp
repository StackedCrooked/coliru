#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <typeinfo>
#include <iostream>

struct PrintType
{
    template<typename T> void operator()(T) const
    {
        std::cout << typeid(T).name() << std::endl;
    }
};

template<typename ...Ts>
void foo(Ts...)
{
    using namespace boost::mpl;
    for_each<vector<Ts...>>(PrintType());
}

struct Widget{};
struct Gadget{};

int main()
{
    foo(1, 1., '1', Widget{}, Gadget{});
}