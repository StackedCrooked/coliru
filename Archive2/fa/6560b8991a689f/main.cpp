#include <string>

template<class S>
struct StringContainer
{};

template<template <class> class TT>
void function(const TT<std::string>& cont) {}

int main()
{
    StringContainer<std::string> s;
    function(s);
}
