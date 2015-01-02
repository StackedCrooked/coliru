//`B<get_item<0,Ts...>>` to `template_with_params<B, ...Ts>`

template <template <typename...> class T, typename... Ts>
struct template_with_params {};

template <typename T>
struct extract_types;

template <template <typename...> class T, typename... Ts>
struct extract_types<T<Ts...>>
{
    using type = template_with_params<T, Ts...>;
};


#include <type_traits>

template <typename T>
struct B {};
template <typename T1, typename T2>
struct BB {};

int main()
{
    static_assert(std::is_same<extract_types<B<int>>::type, template_with_params<B, int>>{}, "!");
    static_assert(std::is_same<extract_types<BB<int, float>>::type, template_with_params<BB, int, float>>{}, "!");
}
