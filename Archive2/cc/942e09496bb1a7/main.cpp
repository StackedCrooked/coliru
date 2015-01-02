#include <cstddef>

template <unsigned int I, typename ...Ts>
struct get_item {};

template <template <typename...> class T, std::size_t N,  typename... Ts>
struct template_with_params {};

template <typename T>
struct extract_template;

template <template <typename...> class T, unsigned int... Is, typename... Ts>
struct extract_template<T<get_item<Is, Ts...>...>>
{
    using type = template_with_params<T, sizeof...(Ts), Ts...>;
};

// Tests:
#include <type_traits>

template <typename T>
struct B {};
template <typename T1, typename T2>
struct BB {};

int main()
{
    static_assert(std::is_same<extract_template<B<get_item<0, int>>>::type,
                               template_with_params<B, 1, int>>{}, "!");
                               
    static_assert(std::is_same<extract_template<BB<get_item<0, int, float>, get_item<1, int, float>>>::type,
                               template_with_params<BB, 2, int, float>>{}, "!");
}
