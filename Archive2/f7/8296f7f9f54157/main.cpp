#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <memory>

template<typename T>
std::size_t my_sizeof(const T& t) {
    return (char*)(std::addressof(t) + 1) - (char*)std::addressof(t);
}

template<typename T>
std::size_t my_sizeof() {
    return (char*)(static_cast<T*>(nullptr) + 1) - (char*)static_cast<T*>(nullptr);
}


int main()
{
    char c = 's';
    std::cout << "char:" << std::endl;
    std::cout << "sizeof(char): " << sizeof(c) << std::endl;
    std::cout << "my_sizeof<char>(): " << my_sizeof(c) << std::endl;
    std::cout << std::endl;
    
    std::cout << "std::vector<int>:" << std::endl;
    std::cout << "sizeof(std::vector<int>): " << sizeof(std::vector<int>) << std::endl;
    std::cout << "my_sizeof<std::vector<int>>(): " << my_sizeof<std::vector<int>>() << std::endl;
}
