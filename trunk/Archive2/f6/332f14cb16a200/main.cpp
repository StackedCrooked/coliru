#include <iostream>
#include <vector>
#include <functional>
#include <type_traits>
#include <boost/type_traits.hpp>

template <std::size_t... Indices>
    struct indices {
    using next = indices<Indices..., sizeof...(Indices)>;
};
template <std::size_t N>
struct build_indices {
    using type = typename build_indices<N-1>::type::next;
};
template <>
struct build_indices<0> {
    using type = indices<>;
};
template <std::size_t N>
using BuildIndices = typename build_indices<N>::type;

template <size_t num_args>
struct unpack_caller
{
private:
    template <typename FuncType, size_t... I>
    auto call(FuncType &f, std::vector<int> &args,     indices<I...>) -> decltype( f(args[I]...) )
    {
        return f(args[I]...);
    }

public:
    template <typename FuncType>
    auto operator () (FuncType &f, std::vector<int>     &args) -> decltype( std::declval<unpack_caller<num_args>>().call(f, args, BuildIndices<num_args>{}) )
    {
        return call(f, args, BuildIndices<num_args>{});
    }
}; 

template<typename InnerType, typename ...Args>
class MFA
{
    std::function<InnerType(Args...)> func;
    
public:
    MFA(InnerType f(Args...))
        : func(f)
    {}

    virtual InnerType calc(std::vector<InnerType> & x)
    {
        return unpack_caller<sizeof...(Args)>()(func, x);
    }
};


int main()
{
    auto fun1 = MFA<int, int, int>([](int x, int y) {return x + y; });
    std::vector<int> arg = std::vector<int>({1, 2});
    fun1.calc(arg);

   return 0;
}
