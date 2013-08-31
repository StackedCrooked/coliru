#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>
#include <memory>

struct deleter
{
    template<class T>
    void operator()(T* t) { delete t; }
};

int main()
{   
    std::unique_ptr<int, deleter> p(new int(6));
    
    std::cout<<*p;
}