#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
std::ostream& operator<<( std::ostream& os, std::vector<T> const & vec ) {
    for( auto & e : vec )
        os << e << " ";
    return os;
}

template <typename Ret, typename In, typename Func>
Ret transform_copy( In const& input, Func&& func) {
    Ret output{};
    std::transform( std::begin(input), std::end(input), std::inserter(output, std::end(output)), std::forward<Func>(func) );
    return output;
}

template <typename In, typename Func>
In transform_copy( In const& input, Func&& func) {
    return transform_copy<In,In,Func>(input, std::forward<Func>(func));
}

int main() {
    std::string str = "abc";
    
    auto r0 = transform_copy( str, [](char b) { return b+1;} );
    std::cout << r0 << "\n";
    
    auto r1 = transform_copy<std::vector<int>>( str, [](char b) { return b+1;} );
    std::cout << r1 << "\n";
    
    auto r2 = transform_copy<std::string>( r1, [](char b) { return b+1;} );
    std::cout << r2 << "\n";
}