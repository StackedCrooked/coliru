#include <boost/utility/in_place_factory.hpp>
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <ostream>

using namespace boost;
using namespace std;

struct Foo: private noncopyable
{
    explicit Foo(int i)
    {
        cout << "construction i=" << i << endl;
    }
};

void make(optional<Foo> &foo)
{
    foo = in_place(11);
}

int main()
{
    optional<Foo> foo;
    cout << "*" << endl;
    make(foo);
    cout << "!" << endl;
}