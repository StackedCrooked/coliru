#include <array>
#include <iostream>

template <class T>
struct foo {};

struct bar
{
    bar () { std::cout << "A" << std::endl; }
    
    template <class T>
	bar(const foo<T>& f) { std::cout << "B" << std::endl; }

	template <class T, class... Ts>
	bar(const foo<T>& f, Ts&&... ts) { std::cout << "C" << std::endl; }
};

int main()
{
	auto f = foo<int>{};
    std::cout << "init g" << std::endl;
    auto g = bar{};
    std::cout << "init h" << std::endl;
    auto h = bar{f};
    std::cout << "init i" << std::endl;
    auto i = bar{f, f};
    std::cout << "fin" << std::endl;
}