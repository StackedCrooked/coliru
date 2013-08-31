#include <vector>

template<template<class, class...> class T, class ...U>
class Test
{
};


int main()
{
    Test<std::vector, int>(); // use default alloctor
}