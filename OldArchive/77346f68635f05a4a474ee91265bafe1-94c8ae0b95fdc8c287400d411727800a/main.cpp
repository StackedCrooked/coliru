#include <map>
#include <unordered_map>

typedef size_t L1Entry;

template<template <typename...> class Container>
class MyClass
{
    typedef Container<int, L1Entry> MapType;
public:
    // ...

private:
    MapType myMap;
};

int main()
{
    MyClass<std::map> obj;
    MyClass<std::unordered_map> obj2;
}