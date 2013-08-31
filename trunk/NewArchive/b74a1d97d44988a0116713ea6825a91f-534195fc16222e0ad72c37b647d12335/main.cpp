#include <tuple>
#include <functional>
#include <iostream>

template<typename ...Args>
class Arguments {
    template<int ...> struct seq { };
    template<int N, int ...S> struct gens : gens<N-1, N-1, S...> { };
    template<int ...S> struct gens<0, S...> { typedef seq<S...> type; };    
    template<typename F, int...S> void do_apply_on(const F & f, seq<S...>) { f(std::get<S>(args_)...); }
    std::tuple<Args...> args_;
    
public:
    template<typename ...A> Arguments(A && ...args) : args_{std::forward<A>(args)...} {}

    template<typename F> void apply_on(const F & f)
    {
        do_apply_on(f, typename gens<sizeof...(Args)>::type());
    }
};


int main()
{
    int i = 0;
    Arguments<int, int> arguments(i, 2);
    arguments.apply_on([](int a, int b) { std::cout << a + b; });
}