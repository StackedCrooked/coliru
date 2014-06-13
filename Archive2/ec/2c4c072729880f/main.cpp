
#include <stdio.h>

template<int i>
struct t 
{
    static constexpr int v = t<i-1>::v+2;
};

template<>
struct t<0>
{
    static constexpr int v = 0;
};

template<int... I>
struct seq;

template<class, template<int> class>
struct transform_impl;

template<int... I, template<int> class F>
struct transform_impl<seq<I...>, F>
{
    using type=seq<F<I>::v ...>;
};

template<class S,template<int> class F>
using transform = typename transform_impl<S,F>::type;

using my_list=seq<0,1,2,3,4,5,6,7,8,9>;

using helper=transform<my_list,t>;

int main() {
    printf("%i\n", t<10>::v);
    //std::cout << t<0>::v << std::endl;
}
