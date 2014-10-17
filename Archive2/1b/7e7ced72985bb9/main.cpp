#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/algorithm.hpp>
#include <iostream>

BOOST_FUSION_DEFINE_STRUCT
(
    (),
    Bar,
    (double, z)
    (char, q)
)

BOOST_FUSION_DEFINE_STRUCT
(
    (),
    Foo,
    (int, x)
    (Bar, y)
)

int main()
{
    using namespace std;
    using namespace boost;
    using namespace fusion;

    Foo f(1, Bar(0.5, '!'));

    for_each(flatten(f), [](auto x)
    {
        cout << x << endl;
    });
}