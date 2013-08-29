#include <iostream>
#include <thread>

template<typename T>
using uT = const T;

template<typename T>
uT<T> foo (T t)
{
    return const_cast<uT<T>>(t);
}