#include <utility>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <cxxabi.h>


std::string Demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}


template<template<typename> class Extended, class T>
Extended<T> make_extended(T&& t)
{
    static_assert(std::is_rvalue_reference<decltype(t)>::value, "");
    static_assert(!std::is_reference<T>::value, "");
    return Extended<T>(std::forward<T>(t));
}


template<typename T>
struct LogConstructor : T
{
    LogConstructor(T t) : T(std::move(t))
    {
        std::cout << Demangle(typeid(T).name()) << " Contructed\n";
    }
};


template<typename T>
struct LogDestructor : T
{
    LogDestructor(T t) : T(std::move(t)) {}
    
    LogDestructor(LogDestructor&&) = default;
    LogDestructor& operator=(LogDestructor&&) = default;
    
    LogDestructor(const LogDestructor&) = default;
    LogDestructor& operator=(LogDestructor&) = default;
    
    ~LogDestructor()
    {
        std::cout << Demangle(typeid(T).name()) << " Destructed\n";
    }
};


struct Item 
{
};


int main()
{
    auto item = make_extended<LogDestructor>(make_extended<LogConstructor>(Item()));
}
