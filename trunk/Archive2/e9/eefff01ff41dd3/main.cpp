template<template<class...> class... packs>
struct blub{};

template<class...>
struct blah{};

int main()
{
    blub<blah, blah, blah>{};
}