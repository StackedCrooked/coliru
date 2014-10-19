#include <type_traits>

template<typename... T>
struct Get;

template<> struct Get<int> { using type = bool; };
template<> struct Get<double> { using type = int; };
template<typename T, typename... Rest>
struct Get<T, Rest...> { using type = double; };

int main()
{
    static_assert(std::is_same<typename Get<double>::type, int>::value, "");
    static_assert(std::is_same<typename Get<int>::type, bool>::value, "");
    static_assert(std::is_same<typename Get<bool, int>::type, double>::value, "");

    return 0;
}