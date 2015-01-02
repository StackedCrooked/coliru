template <unsigned int I, typename ...Ts>
struct get_item {};

template <template <typename...> class T, typename... Ts>
struct template_with_params {};

template <typename T>
struct extract_types;

template <template <typename...> class T, unsigned int... Is, typename... Ts>
struct extract_types<T<get_item<Is, Ts>...>>
{
    using type = template_with_params<T, Ts...>;
};

// Tests:
#include <type_traits>

template <typename T>
struct B {};
template <typename T1, typename T2>
struct BB {};


int main()
{
    static_assert(std::is_same<extract_types<B<get_item<0, int>>>::type, template_with_params<B, int>>{}, "!");
    static_assert(std::is_same<extract_types<BB<get_item<0, int>, get_item<1, float>>>::type, template_with_params<BB, int, float>>{}, "!");
}
