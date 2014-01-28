#include <type_traits>
#include <vector>
#include <iostream>

template<typename T>
class CorrectVector
{
public:
    typedef T value_type;
    typedef T const& const_reference;
    typedef size_t size_type;

    class iterator
    {
    public:
    };
    
    class const_iterator
    {
    public:
        const_iterator() {}
        const_iterator(const iterator&) {}
    };
    
    iterator insert(const_iterator, size_type, const_reference)
    {
        return iterator();
    }
};

template<typename C, typename V	= typename C::value_type, typename It = typename C::iterator>
auto callMultiInsertExplicitInit() ->
	decltype(std::declval<C>().insert(std::declval<It>(), typename C::size_type(), std::declval<V>()))
{
	return 0;
}

int main()
{
    typedef decltype(callMultiInsertExplicitInit<std::vector<int> >()) actual;
    typedef decltype(callMultiInsertExplicitInit<CorrectVector<int> >()) expect;
    std::cout << "platform vector result: " << std::is_void<actual>::value << std::endl;
    std::cout << "correct vector result: " << std::is_void<expect>::value << std::endl;
}
