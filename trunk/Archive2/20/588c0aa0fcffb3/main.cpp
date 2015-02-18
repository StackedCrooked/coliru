#include <cstddef>
#include <type_traits>
#include <tuple>
#include <iostream>
#include <utility>
#include <functional>

template<typename ... Fs>
struct compose_impl
{
    std::tuple<Fs ...> functionTuple;

    compose_impl(Fs&& ... fs) : functionTuple(std::forward_as_tuple(fs ...)) {}

    template<size_t N, typename ... Ts, typename = typename std::enable_if<N==0>::type>
    auto apply(Ts&& ... ts) const
    -> decltype(std::get<0>(this->functionTuple)(std::forward<Ts>(ts)...))
    {
        std::cout << 1 << ":" << N << std::endl;
        return std::get<0>(functionTuple)(std::forward<Ts>(ts)...);
    }

    template<size_t N, typename ... Ts, typename = typename std::enable_if<N!=0>::type>
    auto apply(Ts&& ... ts) const
    -> int
    // -> decltype(this->apply<N-1>(std::get<N>(this->functionTuple)(std::forward<Ts>(ts)...)))
    {
        std::cout << 2 << ":" << N << " " << sizeof...(Ts) << std::endl;
        return apply<N-1>(std::get<N>(functionTuple)(std::forward<Ts>(ts)...));
    }

    template<typename ... Ts>
    auto operator()(Ts&& ... ts) const
    -> decltype(this->apply<sizeof ... (Fs) - 1>(std::forward<Ts>(ts)...))
    {
        std::cout << 3 << std::endl;
        return apply<sizeof ... (Fs) - 1>(std::forward<Ts>(ts)...);
    }
};

template<typename ... Fs>
auto compose(Fs&& ... fs)
-> decltype(compose_impl<Fs ...>(std::forward<Fs>(fs) ...))
{
     return compose_impl<Fs ...>(std::forward<Fs>(fs) ...);
}

int main ()
{
    auto f1 = [](std::pair<double,double> p) {return p.first + p.second;    };
    auto f2 = [](double x) {return std::make_pair(x, x + 1.0); };
    auto f3 = [](double x, double y) {return x*y; };
    auto g = compose(f1, f2, f3);

    std::cout << g(2.0, 3.0) << std::endl;   //prints '13', evaluated as (2*3) + ((2*3)+1)
    return 0;
}
