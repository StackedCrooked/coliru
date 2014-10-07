#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/functional/hash.hpp>
#include <initializer_list>
#include <iostream>
#include <complex>
#include <string>

using namespace std;
using namespace boost;
using namespace fusion;

auto println = [](auto... xs)
{
    initializer_list<int>({(cout << xs << " ", 0)...});
    cout << endl;
};

BOOST_FUSION_DEFINE_STRUCT
(
    (), Foo,
    (int, x)
    (double, y)
)

BOOST_FUSION_DEFINE_STRUCT
(
    (), Bar,
    (complex<double>, u)
    (string, v)
)

auto compose = [](auto f, auto g)
{
    return [=](auto... xs)
    {
        return f(g(xs...));
    };
};

auto apply = [](auto f, auto g, auto... xs)
{
    auto z = zip(xs..., transform(xs, compose(g, g))...);
    for_each(z, [=](auto x)
    {
        invoke(f, x);
    });
};

int main()
{
    Foo a = {1, .1};
    a.x *= 2;
    Bar b = {{1, 2}, "a"};
    b.v += 'b';

    auto double_it = [](auto x) { return x + x; };
    apply(println, double_it, a, b, make_vector(b.v + 'c', cos(b.u)));
}

