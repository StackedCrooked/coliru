#include <iostream>
#include <vector>
#include <iterator>

template<typename It>
void f(It begin) {
    typedef typename It::container_type::value_type value_type;
    std::cout << sizeof(value_type);
}

int main() {
    std::vector<int> v = {1,2,3,4,5,6,7,8};
    f( std::back_inserter( v ) );
}