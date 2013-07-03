#include <utility>

struct X { };

template<typename T>
struct bar
{
    bar(T&& t) : t{std::forward<T>(t)} { }
	T&& t;
};

template<typename T>
auto foo(T&& t)
{
	return bar<T>{std::forward<T>(t)};
}

int main()
{
    X x;
    foo(x);
}
