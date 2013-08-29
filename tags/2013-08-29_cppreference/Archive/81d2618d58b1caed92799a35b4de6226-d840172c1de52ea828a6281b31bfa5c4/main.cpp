#include <iostream>
#include <vector>
#include <list>
#include <boost/range.hpp>

using namespace std;

template<typename...> struct void_ { using type = void; };
template<typename... T> using Void = typename void_<T...>::type;

template<typename... T> using BoostRangeValue = typename boost::range_value<T...>::type;

//////////////////
template<typename T, typename Sfinae = void>
struct range_value {};

template<typename T>
struct range_value<T, Void<BoostRangeValue<T>>>: BoostRangeValue<T> {};

template<typename... T> using RangeValue = typename range_value<T...>::type;
//////////////////

template <typename T, typename C>
    typename enable_if<std::is_same<T, RangeValue<C>>::value, C>::type 
    concat(C c, T v)
{
    c.insert(end(c), v);
    return c;
}

template <typename R, typename C>
    typename enable_if<
        std::is_same< RangeValue<R>, RangeValue<C>
        >::value, C>::type 
    concat(C c, R const& r)
{
    c.insert(end(c), begin(r), end(r));
    return c;
}

//////////////////
// THIS IS CHEATING...
// template<> struct range_value<int, void> {};

//////////////////
int main()
{
    auto v = concat(vector<int> { 1,2,3 }, list<int> { 4,5,6 });
    for(auto i : v)
        std::cout << i << " ";

    // does not SFINAE?
    v = concat(vector<int> { 1,2,3 }, 42);
}

