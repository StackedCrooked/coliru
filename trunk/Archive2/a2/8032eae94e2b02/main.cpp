#include <vector>
#include <string>


template<template<typename> class CRT, typename T>
struct Container
{
    T* data() { return crt().data_impl(); }
    auto size() const { return crt().size_impl(); }
    
    // variable return type. depends on name-hiding    
    auto begin() { return crt().begin_impl(); }
    auto end() { return crt().end_impl(); }
    
private:
    const CRT<T>& crt() const { return static_cast<const CRT<T>&>(*this); }
    CRT<T>& crt() { return static_cast<CRT<T>&>(*this); }
    
    // default implementation
    T* begin_impl() { return data(); }
    T* end_impl() { return begin() + size(); }
};


template<typename T>
struct Array : Container<Array, T>
{
    T* data_impl() { return nullptr; }
    int size_impl() const { return 0; }    
    
    struct iterator {};
    
    iterator begin_impl() { return iterator{}; }
    iterator end_impl() { return iterator{}; }
};


template<typename T>
struct List : Container<List, T>
{    
    T* data_impl() { return 0; }
    int size_impl() const { return 0; }
};


int main()
{    
    // Array has iterator
    Array<int> array;
    Array<int>::iterator array_it = array.begin();
   
    // List has no iterator
    List<int> list;
    int* list_it = list.begin();
}
