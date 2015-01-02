#include <iostream>

//`B<get_item<0,Ts...>>` to `template_with_params<B, ...Ts>`

template <typename T>
struct B {};

template <template <typename...> class T, typename... Ts>
struct template_with_params {};

template <typename T>
struct extract_types;

template <template <typename...> class T, typename... Ts>
struct extract_types<T<Ts...>>
{
    using type = template_with_params<T, Ts...>;
};


template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    TD<extract_types<B<int>>::type>();
}
