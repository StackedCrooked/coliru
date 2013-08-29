#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <bitset>
#include <cstdarg>


#include <vector>

template <typename T>
T sum(const T& v) {
    return v;
}


template <typename T1, typename... Ts>
auto sum(const T1& v1, const Ts&... rest) -> decltype( v1 + sum(rest...) ) {
    return v1 + sum(rest... );
}

// This works fine
/*
template <typename T1, typename... Ts>
auto sum(const T1& v1, const Ts&... rest) -> T1 {
    return v1 + sum(rest... );
}
*/



int main () {
    
    std::cout << sum(1,2);
    std::cout << sum(1,2,3);  // Here is the issue. This works with the commented sum.
    
    return 0;
}


