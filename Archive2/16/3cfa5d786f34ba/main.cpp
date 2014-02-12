#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
const T& constant(const T& t) {
    return t;
}

template<typename T>
struct F {
    void operator ()(T& number) const {
        std::cout << "non-const: " << number << std::endl;
    }
    
    void operator ()(const T& number) const {
        std::cout << "const: " << number << std::endl;
    }
};

int main()
{
    std::vector<int> numbers{1, 2, 3};
    /*std::for_each(numbers.begin(), numbers.end(), F<int>{});
    std::for_each(numbers.cbegin(), numbers.cend(), F<int>{});    
    std::for_each(constant(numbers).begin(), constant(numbers).end(), F<int>{});*/
    
    std::for_each(std::begin(numbers), std::end(numbers), F<int>{});
    const std::vector<int> numbers2{numbers};
    std::for_each(std::begin(numbers2), std::end(numbers2), F<int>{});
    
    return 0;
}
