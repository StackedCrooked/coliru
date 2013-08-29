#include <iostream>
#include <string>
#include <vector>
#include <functional>

template <typename T, typename... Args>
struct printtest
{
    static void go(const T& first, const Args&&... args)
    {
        std::cout << first;
        printtest<Args...>::go(std::forward<const Args>(args)...);
    }
};

template <typename T>
struct printtest<T>
{
    static void go(const T& last)
    {
        std::cout << last << std::endl;   
    }
};


int main()
{
    printtest<int, int, std::string>::go(3,4,"43");
}
