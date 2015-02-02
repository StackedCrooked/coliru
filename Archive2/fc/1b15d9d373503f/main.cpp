#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <utility>

template <typename... Ts>
using void_t = void;

template <typename Functor, typename ... Args>
using FunctorReturn = decltype(std::declval<Functor>()(std::declval<Args>()...));

template <typename Functor, typename Signature, typename = void>
struct FunctorCheck: public std::false_type
{};

template <typename Functor, typename R, typename ... Args>
struct FunctorCheck<Functor, R(Args...), 
    void_t<FunctorReturn<Functor, Args ...>> // SFINAE can kick in here
> : public std::is_same<R, FunctorReturn<Functor, Args ...>>::type
{};

struct F
{
};

int main()
{
    std::cout << FunctorCheck<F, int(int, float, int)>::value << std::endl;
}
