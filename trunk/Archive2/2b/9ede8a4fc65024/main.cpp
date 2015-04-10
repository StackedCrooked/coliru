#include <functional>
#include <boost/signals2/signal.hpp>

namespace bs = boost::signals2;

template<class Signature, class Owner>
class signal
    : private bs::signal<Signature>
{
    friend Owner;
    
    using bs::signal<Signature>::signal;
    
public:
    using bs::signal<Signature>::connect;
};

struct foo
{
    signal<void(), foo> on_stuff;
    
    void test() { on_stuff(); }
};

#include <iostream>

int main()
{
    foo f;
    f.on_stuff.connect([]{ std::cout << "whoo\n"; });
    //f.on_stuff(); // NOPE!
    f.test();
}