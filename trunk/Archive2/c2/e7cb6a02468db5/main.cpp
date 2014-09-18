#include <chrono>
#include <iostream>

template<class T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    print_type<std::chrono::steady_clock::rep>();
    print_type<std::chrono::system_clock::rep>();
    print_type<std::chrono::high_resolution_clock::rep>();
}