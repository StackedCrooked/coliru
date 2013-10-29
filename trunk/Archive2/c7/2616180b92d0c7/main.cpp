#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T, int... Args>
class Container;

template <typename T, int dim, int... Args>
class Container<T, dim, Args...>
{
public:
    Container() {}

    static const int SIZE = dim * Container<T, Args...>::SIZE;
    
protected:
    std::array<T, SIZE> storage;
    
};

template <typename T>
class Container<T>
{
public:
    static const int SIZE = 1;
};


int main()
{   
   Container<float, 5, 3, 7> cont;
   
   std::cout << cont.SIZE;
}