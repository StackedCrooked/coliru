#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/signals2.hpp> 

template<typename T>
struct foo {
    T a;
};

template<typename T>
using AliasName = foo<T>*;

int main() {
    
    
    return 0;
}
