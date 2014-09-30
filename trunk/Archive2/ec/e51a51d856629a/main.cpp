#include <boost/variant.hpp>
#include <iostream>

using namespace std;

struct Foo
{
    void print()
    {
        cout << "Foo" << endl;
    }
};

struct Bar
{
    void print()
    {
        cout << "Bar" << endl;
    }
};

struct action : public boost::static_visitor<void>
{
    template<typename T>
    void operator()(T &x) const
    {
        // T is concrete type here
        x.print(); // call to concrete function, not dynamic dispatch
    }
};

int main()
{
    boost::variant<Foo, Bar> v;

    v = Foo();
    boost::apply_visitor(action(), v);

    v = Bar();
    boost::apply_visitor(action(), v);
}