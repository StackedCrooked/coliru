#include <iterator>
#include <type_traits>
#include <set>
#include <vector>

template<class T> struct dump;

template<class Cont>
using iterator_reference = typename std::iterator_traits<typename Cont::iterator>::reference;

template<class T>
struct test{};

template<class T>
struct test<T&>
{
};

int main()
{
    using type = decltype(true ? std::declval<int&>() : std::declval<int const&>());
    
    dump<type>{};
}