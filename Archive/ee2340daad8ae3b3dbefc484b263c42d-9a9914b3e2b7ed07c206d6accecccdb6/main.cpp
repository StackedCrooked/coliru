#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/mpl/vector.hpp>

#include <iostream>

namespace mpl = boost::mpl;
namespace bte = boost::type_erasure;

struct X {
    void foo(X const&x) 
    { 
        //assert(this == &x);
        std::cout << "this:" << (void*)this << " X::foo: " << typeid(x).name() << " at " << (void*)&x << "\n"; 
    }
};

struct Y {
    void foo(Y const&y) 
    { 
        //assert(this == &y);
        std::cout << "this:" << (void*)this << " Y::foo: " << typeid(y).name() << " at " << (void*)&y << "\n"; 
    }
};

BOOST_TYPE_ERASURE_MEMBER((has_foo), foo, 1)

using reqs = mpl::vector<
    has_foo<void(bte::_self const&)>
    >;

void bar(bte::any<reqs, bte::_self&> a, bte::any<reqs, bte::_self&> b)
{
    a.foo(b);
}

int main()
{
    X x;
    Y y;
    std::cout << "&x = " << (void*)&x << '\n';
    std::cout << "&y = " << (void*)&y << '\n';
    bar(x, y);
}

