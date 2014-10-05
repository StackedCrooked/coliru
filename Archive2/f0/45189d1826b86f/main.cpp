#include <iostream>
#include <type_traits>

namespace detail {
    template<typename T, 
             typename U, 
             bool = std::is_signed<T>::value, 
             bool = std::is_signed<U>::value>
    struct less_than_helper;

    template<typename T, typename U, bool SameSign> 
    struct less_than_helper<T, U, SameSign, SameSign> 
    {
        static bool less_than(T x, U y) { return x < y; }
    };

    template<typename T, typename U> 
    struct less_than_helper<T, U, true, false> 
    {
        static bool less_than(T x, U y) 
        {
            return (x < 0) || 
                   (static_cast<typename std::make_unsigned<T>::type>(x) < y);
        }
    };

    template<class T, typename U> 
    struct less_than_helper<T, U, false, true> 
    {
        static bool less_than(T x, U y) 
        {
            return (y > 0) && 
                   (x < static_cast<typename std::make_unsigned<U>::type>(y));
        }
    };
}

template<class T, class U>
inline bool less_than(T x, U y) 
{
    return detail::less_than_helper<T, U>::less_than(x, y);
}

int main(int argc, char** argv) 
{
    std::cout << less_than(1, 2u) << "\n";
    return 0;
}
