#include <type_traits>

template <typename Needle, template <typename...> class... Haystack>
struct is_one_of : std::false_type {};

template <typename Needle, template <typename...> class Head, template <typename...> class... Tail>
struct is_one_of<Needle, Head, Tail...> : is_one_of<Needle, Tail...>::type {};

template <template <typename...> class Needle, typename... Args, template <typename...> class... Tail>
struct is_one_of<Needle<Args...>, Needle, Tail...> : std::true_type {};


#include <vector>
#include <set>
#include <list>
#include <map>

template<typename X,
         typename Requires = typename std::enable_if<is_one_of<X, std::vector, std::map, std::set>::value>::type>
void htf(X& x) {}

int main()
{
    // This won't fail: vector is on the list
    static_assert(is_one_of<std::vector<int>, std::map, std::list, std::vector, std::set>{}, "!");
    
    std::vector<int> v;
    htf(v); // works fine
        
    std::list<int> l;
    htf(l); // doesn't work, list is not accepted
    
    // This will fail: vector in not in the haystack
    static_assert(is_one_of<std::vector<int>, std::map, std::list, std::set>{}, "!");
}
