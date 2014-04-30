#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

template<typename T, template<typename...> class TT>
struct is_instantiation_of : std::false_type { };

template<template<typename...> class TT, typename...Us>
struct is_instantiation_of<TT<Us...>, TT> : std::true_type { };


template <typename String, template<class> class Allocator>
struct basic_data_object
{
  template<typename T>
  using array_container = std::vector<T, Allocator<T>>;
};



template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value_general
{
    void print() {std::cout << "general\n";}
};
template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value_container
{
    void print() {std::cout << "container\n";}
};


template <typename String, template<class> class Allocator, typename T>
struct get_data_object_value 
    : public std::conditional<
        is_instantiation_of<T, basic_data_object<String,Allocator>::template array_container>::value,
        get_data_object_value_container<String,Allocator,T>,
        get_data_object_value_general<String,Allocator,T>>::type
{
};


#include <list>
int main() {
    static_assert(is_instantiation_of<std::vector<short>,std::vector>::value, "TEST");
    
    get_data_object_value<std::string,std::allocator,std::vector<short>> first;
    first.print();
    get_data_object_value<std::string,std::allocator,std::list<short>> second;
    second.print();
}