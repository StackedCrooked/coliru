#include <boost/optional.hpp>
#include <boost/utility/in_place_factory.hpp>
#include <boost/utility/typed_in_place_factory.hpp>
#include <iostream>


struct Foo
{
    explicit Foo(int n, int m) : n(n + m) {}
    
    Foo(const Foo&) = delete;
    Foo& operator=(const Foo&) = delete;
    
    int n;
};



int main()
{
    boost::optional<Foo> a(boost::in_place(1, 2));
    std::cout << a->n << std::endl;
}
