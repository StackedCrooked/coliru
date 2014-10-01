struct halt;
template<template<typename...> class Alias, typename... Args> struct rec;

template<typename... Args> struct handle;

template<>
struct handle<> {};

template<typename Arg, typename... Args>
struct handle<Arg, Args...>
: handle<Args...> {};

template<template<typename...> class Alias, typename... R, typename... Args>
struct handle<rec<Alias, R...>, Args...>
: Alias<R...>, handle<Args...> {};

template<typename... Args>
struct handle<halt, Args...> {
    template<typename...> struct dependent {};
    
    static_assert( (dependent<Args...> {}, false), "halt" );
};

int main()
{
    handle<int, rec<handle, int&, rec<handle, int*, halt, long*>, long&>, long> {};
}