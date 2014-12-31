#include <type_traits>

template <template <typename...> class T>
struct TPL {};

template <typename Needle, typename... Haystack>
struct is_one_of : std::false_type {};

template <typename Needle, typename Head, typename... Tail>
struct is_one_of<Needle, Head, Tail...> : is_one_of<Needle, Tail...>::type {};

template <template <typename...> class Needle, typename... Args, typename... Tail>
struct is_one_of<Needle<Args...>, TPL<Needle>, Tail...> : std::true_type {};

template <typename Needle, typename... Tail>
struct is_one_of<Needle, Needle, Tail...> : std::true_type {};

#include <vector>
#include <set>
#include <list>
#include <map>

template<typename X,
         typename Requires = typename std::enable_if<is_one_of<X, TPL<std::vector>, TPL<std::map>, TPL<std::set>>::value>::type>
void htf(X& x) {}

int main()
{
    // This won't fail: vector is on the list
    static_assert(is_one_of<std::vector<int>, TPL<std::map>, TPL<std::list>, TPL<std::vector>, TPL<std::set>>{}, "!");
    
    // Mixed list
    static_assert(is_one_of<std::vector<int>, TPL<std::map>, std::vector<float>, std::vector<int>, TPL<std::set>>{}, "!");
    
    std::vector<int> v;
    htf(v); // works fine
        
    std::list<int> l;
    htf(l); // doesn't work, list is not accepted
    
    // This will fail: vector in not in the haystack
    static_assert(is_one_of<std::vector<int>, std::map, std::list, std::set>{}, "!");
}
