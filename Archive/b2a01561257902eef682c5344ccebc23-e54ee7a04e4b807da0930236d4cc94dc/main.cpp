#include <tuple>
#include <type_traits>

int main()
{
    using my_tuple = std::tuple<int, bool, char>;
    static_assert(std::is_same<std::tuple_element<0, my_tuple>::type, int>::value, "!");
    static_assert(std::is_same<std::tuple_element<1, my_tuple>::type, bool>::value, "!");
    static_assert(std::is_same<std::tuple_element<2, my_tuple>::type, char>::value, "!");
}
