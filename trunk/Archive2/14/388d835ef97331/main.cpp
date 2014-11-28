#include <iostream>
#include <iomanip>

    namespace detail
    {
        template <int ...Args>
        struct CompFunc;

        template <int num, int ...Args>
        struct CompFunc<num, Args...>
        {
            static constexpr bool f(int i)
            {
                return (i == num) || CompFunc<Args...>::f(i);
            }
        };
        template <>
        struct CompFunc<>
        {
            static constexpr bool f(int i)
            {
                return false;
            }
        };
    }

    template <int ...Args>
    constexpr bool any_of_const(int i)
    {
        return detail::CompFunc<Args...>::f(i);
    }
    
int main()
{
    std::cout << std::boolalpha;
    std::cout << any_of_const<1, 2, 3, 4, 5, 6, 7, 8, 9>(5) << std::endl;
    std::cout << any_of_const<1, 2, 3, 4, 5, 6, 7, 8, 9>(54) << std::endl;
}
