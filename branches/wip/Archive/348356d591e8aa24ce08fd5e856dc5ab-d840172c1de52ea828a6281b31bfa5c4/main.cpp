#include <iostream>
#include <vector>
#include <list>
#include <boost/range.hpp>

using namespace std;

template<typename...> struct void_ { using type = void; };
template<typename... T> using Void = typename void_<T...>::type;

template<typename T, typename Sfinae = void>
struct range_value {};

template<typename T>
struct range_value<T, Void<typename boost::range_value<T>::type>>: boost::range_value<T> {};

template <typename T, typename C>
    typename enable_if<std::is_same<T, typename range_value<C>::type>::value, C>::type 
    concat(C c, T v)
{
    c.insert(end(c), v);
    return c;
}

template <typename R, typename C>
    typename enable_if<std::is_same<
        typename range_value<R>::type, 
        typename range_value<C>::type>::value, C>::type 
    concat(C c, R const& r)
{
    c.insert(end(c), begin(r), end(r));
    return c;
}

int main()
{
    auto v = concat(vector<int> { 1,2,3 }, list<int> { 4,5,6 });
    for(auto i : v)
        std::cout << i << " ";

    // does not SFINAE?
    v = concat(vector<int> { 1,2,3 }, 42);
}
