#include <type_traits>

enum class EC { a, b };
enum E { c, d };

template <typename T>
auto is_enum_class_impl(int) -> decltype((void)+T{}, std::false_type{});

template <typename T>
auto is_enum_class_impl(...) -> std::true_type;

template <typename T>
using is_enum_class = std::integral_constant<bool, decltype(is_enum_class_impl<T>(0))::value && std::is_enum<T>::value>;

int main()
{
    static_assert(is_enum_class<EC>::value, "!");
    static_assert(!is_enum_class<E>::value, "!");
    static_assert(!is_enum_class<int>::value, "!");
}
