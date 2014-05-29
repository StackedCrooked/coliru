namespace fake_std {
    
// what if vector template accepted only one template param

// if we used T for vector<T>
template<typename T>
struct vector<T> : basic_vector<T, allocator<T>>
{
}; 


// then we could use Traits<T> for basic_vector<T, alloc>:
template<template<typename> class Traits, typename T>
struct vector<Traits<T>> : basic_vector<T, typename Traits<T>::allocator> {}


