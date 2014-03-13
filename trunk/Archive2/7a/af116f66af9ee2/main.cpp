#include <iostream>
using namespace std;

using _true  = integral_constant <bool, true>;
using _false = integral_constant <bool, false>;

template <typename T> using pass = _true;

template <template <typename...> class F>
struct temp { };

template <typename... A, template <typename...> class F>
static F <A...> subs_fun(temp <F>);

template <template <typename...> class F, typename... A>
using subs = decltype(subs_fun <A...>(temp <F>()));

template <template <typename...> class F>
struct test
{
    template <typename... A> static _false                 _(...);
    template <typename... A> static pass <subs <F, A...> > _(int);
};

template <template <typename...> class F, typename... A>
using sfinae = decltype(test <F>::template _<A...>(0));

template <typename T> using type_of  = typename T::type;
template <typename T> using has_type = sfinae <type_of, T>;

struct A { using type = double; };

int main()
{
    cout << has_type <int>() << ", ";
    cout << has_type <A>()   << endl;
}
