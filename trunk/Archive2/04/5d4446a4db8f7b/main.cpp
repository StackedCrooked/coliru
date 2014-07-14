#include <iostream>
#include <functional>
#include <memory>
#include <utility>

void print(std::unique_ptr<int> const& p)
{
    std::cout << "unique_ptr(" << (p ? "non-empty" : "empty") << ")";
}
template<class T>
void print(T const& t)
{
	std::cout << t;
}

template<class... Args>
void foo(Args... args)
{
	std::cout << __PRETTY_FUNCTION__ << ": ";
	int _[] = {(print(args), std::cout << " ; ", 0)..., 0};
	(void)_;
	std::cout << "\n";
}

struct wrapper
{
	template<class... Args>
	int operator()(Args&&... args)
	{ foo(std::forward<Args>(args)...); return 42; }
};

namespace std
{
	template<> struct is_bind_expression<wrapper> : true_type {};
}

void bar(int i, std::unique_ptr<int> p, int j)
{
	std::cout << "bar: ";
	print(i);
	std::cout << " ; ";
	print(p);
	std::cout << " ; ";
	print(j);
	std::cout << "\n";
}

int main()
{
	std::cout << std::boolalpha;
	auto b = std::bind(bar, wrapper(), std::placeholders::_1, std::placeholders::_2);
	b(std::unique_ptr<int>{new int}, 21);
}