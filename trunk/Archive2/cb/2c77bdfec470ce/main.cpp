#include <iostream>
#include <vector>
#include <tuple>

int main() {
    typedef std::vector<int> vector_type;

    vector_type v = { 1, 2, 3 };

    vector_type::difference_type 
        first     = 0,
        last      = v.size(),
        direction = -1; // or +1

    if(direction < 0) {
        std::tie(first, last) = std::make_tuple(last-1, first-1);
    }

    for(auto i = first; i != last; i += direction) {
        std::cout << v[i] << '\n';
    }
}
