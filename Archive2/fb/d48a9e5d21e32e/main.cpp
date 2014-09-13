#include <iostream>

#include <string>
#include <vector>
#include <type_traits>




template<typename Func>
auto DeduceType(Func&& f) -> typename std::enable_if<std::is_same<typename std::result_of<Func()>::type, void>::value, int>::type
{
    f();
    return 0;
}

template<typename Func>
auto DeduceType(Func&& f) -> typename std::enable_if<std::is_same<typename std::result_of<Func()>::type, int>::value, int>::type
{
	return f();
}

void f()
{
}

int g()
{
    return 100;
}


int main()
{
   std::cout << DeduceType(f) << "\n";
   std::cout << DeduceType(g) << "\n";

}
