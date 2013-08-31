#include <iostream>
#include <vector>


// A vector which allows the easier () notation as an alternative to [].
template<typename T>
struct EasyVector : std::vector<T>
{
    using base_type = std::vector<T>;
    using base_type::base_type;
    
    const T& operator()(std::size_t i) const { return base_type::operator[](i); }
    T& operator()(std::size_t i) { return base_type::operator[](i); }
};

int main()
{
    EasyVector<int> vec = {1, 2, 3};
    std::cout << vec(0) << std::endl;
    std::cout << vec(1) << std::endl;
    std::cout << vec(2) << std::endl;
}