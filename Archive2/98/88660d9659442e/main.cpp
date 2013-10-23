#include <vector>
#include <iostream>

template <typename A, typename B>
A add(A a, B b)
{
 return a + b;   
}

template <typename A, typename B, typename C>
A add(A a, B b, C c)
{
 return a + b + c;   
}

template <typename A, typename B, typename... Args>
A add(A a, B b, Args... args)
{
    return add(a + b, args...);
}

int main()
{
    std::cout << add(1, 2);
    std::cout << add(1, 2, 3);
    std::cout << add(1, 2, 3, 4);

	std::cin.get();
}