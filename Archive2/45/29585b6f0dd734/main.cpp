#include <iostream>
#include <typeinfo>

template <unsigned int N, template <class...> class ClassName, class ... InsideClass>
struct GetNthTypeOfNested;

template<unsigned int N, template<class...> class ClassName, class FirstOfInsideClass, class ... RestOfInsideClass>
struct GetNthTypeOfNested<N, ClassName, FirstOfInsideClass, RestOfInsideClass...>
: GetNthTypeOfNested<N - 1, ClassName, RestOfInsideClass...>
{};

template<template<class...> class ClassName, class First, class ... InsideClass>
struct GetNthTypeOfNested<0, ClassName, First, InsideClass...>
{
  typedef First type;
};

template<typename ... Args> struct Typer;
template<>
struct Typer<>{

};

template<typename First,typename ... Args>
struct Typer<First,Args...>:Typer<Args...>{
  template<unsigned int N>
    void get(){
      std::cout << typeid(typename GetNthTypeOfNested<N, Typer, First, Args...>::type).name() << std::endl;
    }
};

int main ()
{
  Typer<int, float, double> f; f.get<1>();
}
