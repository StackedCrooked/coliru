#include <vector>
#include <iostream>

template<class T>
struct my_special_allocator
    : std::allocator<T>{};

template<class T>
using my_vector = std::vector<T, my_special_allocator<T>>;

int main()
{
    my_vector<int> v{1,2,3};
    for(auto& e : v)
        std::cout << e << " ";
}
