#include <iostream>
#include <utility>

#include <boost/type_erasure/free.hpp>
#include <boost/type_erasure/any.hpp>
#include <boost/mpl/vector.hpp>

using namespace std;
using namespace boost;
using namespace type_erasure;

BOOST_TYPE_ERASURE_FREE((has_action), action, 1)

using any_with_action = any<mpl::vector<copy_constructible<>, has_action<void(_self&)>>>;

struct Foo{};
struct Bar{};

void action(Foo&)
{
    cout << "Foo" << endl;
}

void action(Bar&)
{
    cout << "Bar" << endl;
}

int main()
{
    any_with_action x = Foo{}, y = Bar{};
    action(x);
    action(y);
}