#include <boost/type_erasure/any.hpp>
#include <boost/type_erasure/member.hpp>
#include <boost/mpl/vector.hpp>

#include <iostream>

namespace mpl = boost::mpl;
namespace bte = boost::type_erasure;

struct X
{
    X() = default;
    X(std::vector<X> const&);
    void foo() { std::cout << "X::foo()" << std::endl; }
    void foo(X const&) { std::cout << "X::foo(X const&)" << std::endl; }
    void bar(std::vector<X>) { std::cout << "X::bar()" << std::endl; }
};

struct Y
{
    void foo() { std::cout << "Y::foo()" << std::endl; }
    void foo(Y const&) { std::cout << "X::foo(X const&)" << std::endl; }
    void bar(std::vector<Y>) { std::cout << "Y::bar()" << std::endl; }
};

BOOST_TYPE_ERASURE_MEMBER((has_foo), foo, 0)
BOOST_TYPE_ERASURE_MEMBER((has_bar), bar, 1)

using reqs = mpl::vector<
    has_foo<void(bte::_self const&)>
    >;

void bar(bte::any<reqs, bte::_self&> awf)
{
    //awf.foo();
}

int main()
{
    X x;
    bar(x);

    Y y;
    bar(y);
}
