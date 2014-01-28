#include <type_traits>
#include <vector>
#include <iostream>

    template<typename C, typename V	= typename C::value_type, typename It = typename C::iterator>
	auto callMultiInsertExplicitInit() ->
		decltype(std::declval<C>().insert(std::declval<It>(), typename C::size_type(), std::declval<V>()))
	{
		return 0;
	}

int main()
{
    typedef decltype(callMultiInsertExplicitInit<std::vector<int> >()) foo;
    std::cout << std::is_void<foo>::value << std::endl;
}
