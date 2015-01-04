#include <iostream>
#include <tuple>

template<std::size_t n, std::size_t i>
struct IterateFunctor
{
    template<typename Tuple, typename Functor>
	void operator()(Tuple & tuple, Functor functor)
	{
		functor(std::get<n>(tuple));
		IterateFunctor<n + 1, i - 1> Iterator;
		Iterator(tuple, functor);
	}
};

template<std::size_t n>
struct IterateFunctor<n, 0>
{
	template<typename T, typename Functor>
	void operator()(T &, Functor)
	{}
};

template<typename Functor, typename Tuple>
void Iterate(Tuple & tuple, Functor functor)
{
	IterateFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

template<typename Functor, typename Tuple>
void Iterate(Tuple const & tuple, Functor functor)
{
	IterateFunctor<0, std::tuple_size<Tuple>::value> iterator;
	iterator(tuple, functor);
}

int main()
{
	int i = 0;
	char const * j = "blah";
	float k = 1.2;

	Iterate(std::tie(i, j, k), [](auto x)
	{
		std::cout << x << "\n";
	});
}