#include <type_traits>

template <class T>
struct Allocator {
    using Type_ = T;
};

template <class T, class Alloc_ = Allocator<T>>
struct Container
{
	using Allocator_ = Alloc_;
	using Type_ = T;
};

template <
	class Container_,
		//enable if container have allocator and type of allocator is correct
		typename std::enable_if <
		(std::is_same<Container_, Container<typename Container_::Type_>>::value
		|| std::is_base_of<Allocator<typename Container_::Type_>,
		typename Container_::Allocator_>::value) &&
		std::is_same<typename Container_::Type_, typename  Container_::Allocator_::Type_
		>::value,//is_same
		int>::type/*enable_if*/ = 0
>
struct Graph {};


template <class T>
struct MyAllocator :public Allocator<T>
{
	using Type_ = T;
};

int main(int argc, char *argv[])
{
	Graph<Container<int> > a;
	Graph<Container<char,MyAllocator<char>> > b;
}