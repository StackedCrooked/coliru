#include <type_traits>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace concept {
    namespace detail {
        
        template<typename T, 
                 typename R = decltype(std::declval<T>() < std::declval<T>())>
        constexpr bool is_ord(T *) { 
            return std::is_same<R, bool>::value; 
        }
        
        constexpr bool is_ord(...) { 
            return false; 
        }
    }
    
    template<typename T>
    constexpr bool is_ord() { 
        return detail::is_ord( static_cast<T*>(nullptr) ); 
    }
}

template<typename T>
inline void merge_sort(std::vector<T>& v)
{
    static_assert( concept::is_ord<T>(), "Element type is not sortable" );
    sort(begin(v), end(v)); // ... just use std::sort here for example's sake.
}

struct type
{
    int x;
    type(int x) : x{x} {}
    explicit operator int() const { return x; }
    //bool operator<(type const& b) const { return x < b.x; }
};

// bool operator<(type const&, type const&) { return true; }

int main()
{
    std::vector<type> v = {3,2,1};
    merge_sort(v);
    for(auto x : v)
        std::cout << static_cast<int>(x) << " ";
    std::cout << std::endl;
    return 0;
}
