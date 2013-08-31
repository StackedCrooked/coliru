#include <type_traits>
#include <iostream>

template <typename T, typename U>
void print_same() {
    std::cout << std::boolalpha << std::is_same<T, U>() << "\n";
}

int main()
{
    char a[8];
    char b[12];
    
    print_same<decltype(a), char[8]>();
    print_same<decltype(b), char[12]>();
    print_same<decltype(1 ? a : b), char*>();
    print_same<decltype(1 ? a : b), char[8]>();
    print_same<decltype(1 ? a : b), char[12]>();
}
