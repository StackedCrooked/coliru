#include <iterator>
#include <type_traits>

#define AUTO_RETURN(...) \
 noexcept(noexcept(__VA_ARGS__)) -> decltype(__VA_ARGS__) {return (__VA_ARGS__);}

template <typename T>
constexpr auto decayed_begin(T&& c)
AUTO_RETURN(std::begin(std::forward<T>(c)))

template <typename T>
constexpr auto decayed_end(T&& c)
AUTO_RETURN(std::end(std::forward<T>(c)))

template <typename T,
          typename std::enable_if<std::is_array<T>::value, std::size_t>::type N>
constexpr typename std::remove_all_extents<T>::type* decayed_begin(T(&c)[N])
{
    return decayed_begin(*c);
}

template <typename T,
          typename std::enable_if<std::is_array<T>::value, std::size_t>::type N>
constexpr auto decayed_end(T(&c)[N])
AUTO_RETURN( reinterpret_cast<typename std::remove_all_extents<T>::type*>(c + N))


#include <iostream>

int main()
{
    int arr[4][3][2] { 2, 3, 5, 7, 11,
                       13, 17, 19, 23, 29,
                       31, 37, 41, 43, 47,
                       53, 59, 61, 67, 71,
                       73, 79, 83, 89 };

    std::copy( decayed_begin(arr), decayed_end(arr), std::ostream_iterator<int>(std::cout, " ") );
}
