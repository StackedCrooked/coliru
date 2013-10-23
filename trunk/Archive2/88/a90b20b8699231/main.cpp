#include <vector>
#include <iostream>

template <typename A>
void print(A a)
{
 std::cout << a;   
}

template <typename A, typename... Args>
void print(A a, Args... args)
{
 print(a);
 print(args...);
}

int main()
{
    print("This ", "is ", "a ", "sentence.");
	std::cin.get();
}