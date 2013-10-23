#include <vector>
#include <iostream>

template <typename A, typename B, typename... Args>
int add(A a, B b, Args... args)
{
 return add(a + b, args);
}

int main()
{
    std::cout << add(1, 2, 3);

	std::cin.get();
}