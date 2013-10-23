#include <vector>
#include <iostream>

int add()
{
 return 0;
}

template<typename T>
int add(T a) {
    return a;
}

template <typename A, typename B, typename... Args>
int add(A a, B b, Args... args)
{
 return add(a + b, args...);
}

int main()
{
    std::cout << add();
    std::cout << add(1, 2, 3, 4, 5);

	std::cin.get();
}