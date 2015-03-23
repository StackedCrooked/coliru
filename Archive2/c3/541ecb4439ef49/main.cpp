#include <iostream>
#include <type_traits>

template<class T, class Alloc = std::allocator<T>> class std::vector; 

template<class T>
struct is_vector : std::false_type { };

template<class T, class Alloc>
struct is_vector<std::vector<T, Alloc>> : std::true_type { };


#include <vector>

int main()
{
    std::cout << is_vector<std::vector<int>>::value << std::endl;
}
