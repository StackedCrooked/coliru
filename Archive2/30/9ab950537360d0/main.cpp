#include <string>
#include <type_traits>

template<typename T, typename U, typename... Us>
struct is_any_of
    : std::integral_constant<
        bool,
        std::conditional<
            std::is_same<T,U>::value,
            std::true_type,
            is_any_of<T,Us...>
        >::type::value
      >
{ };

template<typename T, typename U>
struct is_any_of<T,U> : std::is_same<T,U>::type { };

template<typename T>
void myFunc(T data)
{
    static_assert( is_any_of<T, int, char, std::string>{}, "T not allowed");
}

int main()
{
    myFunc(0);    // ok
    myFunc(0ul);  // error
}