#include <iostream>
#include <string>
#include <chrono>

template <typename C>
void println_UniversalReference(C && c)
{
    for (auto && v : c) std::cout << v << ' ';
    std::cout << '\n';
}

template <typename C>
void println_Value(C c)
{
    for (auto && v : c) std::cout << v << ' ';
    std::cout << '\n';
}

int main()
{
    {
        auto start = std::chrono::steady_clock::now();
        println_Value(std::string{"abc"});
        auto end = std::chrono::steady_clock::now();
        std::clog << "[println_Value]; Time elapsed: " <<  std::chrono::duration<double>(end - start).count() << std::endl;
    }
    
    {
        auto start = std::chrono::steady_clock::now();
        println_UniversalReference(std::string{"abc"});
        auto end = std::chrono::steady_clock::now();
        std::clog << "[println_UniversalReference]; Time elapsed: " <<  std::chrono::duration<double>(end - start).count() << std::endl;
    }
}
