#include <iostream>

// dummy classes
class Foo {};
class Bar {};

// dummy Fun
void Fun(Foo, Bar)
{
    std::cout << "Fun";
}

// function for printing parameter packs
template <typename T>
void print(T arg)
{
    std::cout << arg << " ";
}

template <class Head, class... Tail>
void print(Head head, Tail... tail)
{
	std::cout << head << " ";
	print(tail...);
}

// dummy CalcFoo
template< class... T >
Foo CalcFoo(T... args)
{
	// just prints its arguments
	print(args...);
	return Foo{};
}

// helper struct, rotates arguments N times to the left
template <size_t N>
struct MoreFunHelper
{
	template <class Head, class... Tail>
	static void RotateLeft(Head head, Tail... tail)
	{
		// N is not zero, do the rotate
		MoreFunHelper<N - 1>::RotateLeft(tail..., head);
	}
};

template <>
struct MoreFunHelper<0>
{
	template <class Head, class... Tail>
	static void RotateLeft(Head head, Tail... tail)
	{
		// N is zero, head is now the last of the original arguments, tail is the first part of the original arguments
		// call OPs functions
		Fun(CalcFoo(tail...), head);
	}
};

template< class... T >
void MoreFun(T... args)
{
	// call the helper, rotate the arguments
	MoreFunHelper<sizeof...(T) - 1>::RotateLeft(args...);
}

int main()
{
	MoreFun(1, 2, 3, 4, 5, Bar{});
}