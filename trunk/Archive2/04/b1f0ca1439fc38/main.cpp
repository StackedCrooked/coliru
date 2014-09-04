#include <iostream>

template<typename Last>
auto add(Last last)
{
    return last;
}
template<typename First, typename... Rest>
auto add(First first, Rest... rest)
{
    return first + add(rest...);
}

int main()
{
    std::cout << add(1) << std::endl;
    std::cout << add(1, 2) << std::endl;
    std::cout << add(1, 2, 3) << std::endl;
    std::cout << add(1, 2, 3, 4) << std::endl;
}
