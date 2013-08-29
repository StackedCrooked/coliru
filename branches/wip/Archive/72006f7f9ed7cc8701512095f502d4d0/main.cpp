#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>
#include <memory>


template<class T>
struct deleter
{
    void operator()(T* t) { delete t; }
};

template<typename T>
using up = std::unique_ptr<T, deleter<T>>;

int main()
{   
    up<int> p(new int(6));
    
    std::cout<<*p;
}