#include <memory>
#include <iostream>
#include <boost/signals2.hpp>

struct X
{
    ~X() { std::cout << "~X()" << std::endl; }
    void add_handler(std::function<void()> handler) 
    { event.connect(handler); }
    boost::signals2::signal<void()> event;
};

struct Y
{
    Y(std::shared_ptr<X> x) : _x{std::move(x)} { }
    ~Y() { std::cout << "~Y()" << std::endl; }
    void foo() { }
    std::shared_ptr<X> _x;
};

int main()
{
    auto x = std::make_shared<X>();
    auto y = std::make_shared<Y>(x);
    x->add_handler(std::bind(&Y::foo, y));
}