#include <iostream>

template<typename T>
const T& min(const T& t)
{
    return t;
}

template<typename Head, typename ...Args>
typename std::common_type<Head, Args...>::type min(const Head& h, Args&& ...args)
{
    return std::min<typename std::common_type<Head, Args...>::type>(h, min(std::forward<Args>(args)...));
}

int main()
{
    std::cout << min(3, 4ul, 2, 9u);
}