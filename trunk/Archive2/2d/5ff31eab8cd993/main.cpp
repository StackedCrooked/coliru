#include <boost/signals2/signal.hpp>
#include <iostream>

using my_event = boost::signals2::signal<void(int, char)>;

#define SLOT(name) [this] (auto&&... args) { name (std::forward<decltype(args)>(args)...); }

struct X
{
    X(my_event& e)
    {
        e.connect(SLOT(foo));
    }
    
    void foo(int x, char c)
    {
        std::cout << x << " " << c;
    }
};

int main() 
{
    my_event e;
    
    X x{e};
    
    e(42, 'c');
}