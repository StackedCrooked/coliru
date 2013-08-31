#include <boost/range/adaptor/transformed.hpp>
#include <initializer_list>
#include <iostream>
#include <utility>

using namespace std;

template<typename F>
struct Transformer
{
    F f; // need C++14 polymorphic lambda  :crash:
    template<typename R>
    auto operator()(const R &x) const
    {
        return boost::adaptors::transform(x, f);
    }
};

struct EmptyList{} const empty_list;

#define UNARY_FUNC(name, body) \
struct AUX_ ## name \
{ \
    template<typename T> \
    auto operator()(const T &x) const \
    { \
        return body; \
    } \
} const name \
/**/

UNARY_FUNC(fst, x.first);
UNARY_FUNC(snd, x.second);
UNARY_FUNC(id, x);
UNARY_FUNC(map, (Transformer<T>{x}) );

UNARY_FUNC(foo, make_pair(x(fst), x(snd)) );
UNARY_FUNC(bar, x(make_pair(id, empty_list)) );

int main()
{
    auto result = make_pair(foo(bar), foo(map));
    auto data = {make_pair(1, 11), make_pair(2, 22) };

    for(auto z : result.second.first(data) )
        cout << z << " ";
    cout << endl;

    for(auto z : result.second.second(data) )
        cout << z << " ";
    cout << endl;
}
