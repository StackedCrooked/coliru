#include <iostream>

template<typename T>
constexpr T min(T&& t) noexcept
{
    return std::forward<T>(t);
}

template<typename Head, typename ...Args>
constexpr typename std::common_type<Head, Args...>::type min(Head&& h, Args&& ...args) noexcept
{
    return std::min<typename std::common_type<Head, Args...>::type>(std::forward<Head>(h), min(std::forward<Args>(args)...));
}

int main()
{
    std::cout << min(3, 4ul, 2, 9u);
}