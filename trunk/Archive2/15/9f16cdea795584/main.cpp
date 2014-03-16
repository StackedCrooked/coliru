#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <iostream>

struct X
{
    int foo() const 
    {
        return 42;
    }
    virtual ~X() {
        std::cout << "I'm stepping out here\n";
    }
};

int weak_call(int (X::*ptmf)() const, boost::weak_ptr<X> const& wp) 
{
    auto lock = wp.lock();
    if (!lock)
        throw boost::bad_weak_ptr();

    return ((*lock).*ptmf)();
}

int main()
{
    boost::function<int()> bound_foo;

    {
        auto x = boost::make_shared<X>(); 
        bound_foo = boost::bind(weak_call, &X::foo, boost::weak_ptr<X>(x));

        std::cout << "Bound foo returns: " << bound_foo() << "\n";
    }

    // the bind expression keeps the shared pointer alive
    std::cout << "Bound foo returns: " << bound_foo() << "\n";
}
