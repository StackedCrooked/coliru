#include <vector>
#include <iostream>

template<class T>
class Allocator{};

template<class T, class Alloc = Allocator<T>>
class Container
{
    using Allocator = Alloc;
};

template < class Container,
	typename std::enable_if<
	std::is_same<typename Container::Allocator, Container< Allocator>>{}  >::type
>
struct Graph
{
};

int main(int argc, char *argv[])
{
	Graph<Container<int>>;
}
