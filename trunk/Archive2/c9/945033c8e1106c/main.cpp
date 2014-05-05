#include <iostream>
#include <map>
#include <string>
#include <vector>

template <typename> void magic();

template <typename T>
struct Impl 
{
    static void f() { std::cout << "Primary template\n"; }
};

template <typename T, typename A>
struct Impl<std::vector<T, A>>
{
    static void f() { std::cout << "A vector\n"; magic<T>(); }
};

template <typename K, typename T, typename P, typename A>
struct Impl<std::map<K, T, P, A>>
{
    static void f() { std::cout << "A map\n"; magic<K>(); magic<T>(); }
};

template <typename T> void magic() { Impl<T>::f(); }

int main()
{
    magic<std::vector<std::map<std::string,std::vector<int>>>>();
}