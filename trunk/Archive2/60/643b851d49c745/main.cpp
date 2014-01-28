#include <type_traits>

    template<typename C, typename V	= typename C::value_type, typename It = typename C::const_iterator>
	auto callMultiInsertExplicitInit() ->
		decltype(std::declval<C>.insert(std::declval<It>(), typename C::size_type(), std::declval<V>()))
	{
		return decltype(std::declval<C>.insert(std::declval<It>(), typename C::size_type(), std::declval<V>()))();
	}

int main()
{
}
