#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <type_traits>
#include <iterator>



namespace handle
{
    
    template <typename T, typename V>
    static auto max(const T& x, const V& y)  
    -> typename std::common_type<T,V>::type
    {
        return x > y ? x : y;
    }

    template <typename T, typename V, typename... Args>
    static auto max(const T& x, const V& y, const Args&... args) 
    -> typename std::common_type<T, typename std::common_type<V, Args...>::type >::type
    {
        return max(x, max(y, args...));
    }
}


int main()
{
    std::cout << handle::max(1,2,3.3); // fails
}


