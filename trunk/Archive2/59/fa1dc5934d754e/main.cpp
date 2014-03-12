#include <tuple>

template <int N, class F, class... Args, class... Types>
auto call(F f, Args... args, std::tuple<Types...> const& t) noexcept -> decltype(auto)
{

}

int main()
{
    return 0;    
}