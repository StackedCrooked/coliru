#include <iostream>
#include <string>
#include <vector>
#include <tuple>


auto list = std::make_tuple(1, 2, 3, 4);

/// Work like a charm
template <class T>
auto test1(T &&brush) -> decltype(std::get<0>( std::forward<T>(brush) )) {
    return std::get<0>( std::forward<T>(brush) );
}


/// And now - C++14 feature
/// fail to compile - return value, instead of reference
template <class T>
auto test2(T &&brush) {
    return std::get<0>( std::forward<T>(brush) );
}

int main()
{
    auto &t1 = test1(list);
    auto &t2 = test2(list);        
}

