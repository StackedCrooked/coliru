#include <utility>
#include <type_traits>

template<class...> class B {};

namespace detail
{
    template <typename T>
    struct is_derived_from_B
    {
        template <typename... Args>
        static std::true_type test(B<Args...>*);

        static std::false_type test(void*);

        static constexpr bool value = decltype(test( std::declval<T*>() )){};
    };
}

template <typename T>
struct is_derived_from_B : std::integral_constant<bool, detail::is_derived_from_B<T>::value>
{
};

int main()
{
}