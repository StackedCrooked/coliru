#include <iostream>

template<typename T>
T min(T&& t)
{
    return std::forward<T>(t);
}

template<typename Head, typename ...Args>
typename std::common_type<Head, Args...>::type min(Head&& h, Args&& ...args)
{
    return std::min<typename std::common_type<Head, Args...>::type>(h, min(std::forward<Args>(args)...));
}

int main()
{
    std::cout << min(3, 4ul, 2, 9u);
}