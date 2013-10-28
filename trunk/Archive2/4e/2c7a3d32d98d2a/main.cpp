#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T1, int... Args>
class Container;

template <typename T1, int dim, int... Args>
class Container<T1, dim, Args...> : public Container<T1, Args...>
{
public:
    Container() : Container<T1, Args...>() {}

    constexpr static int nTemplArgs = dim * Container<T1, Args...>::nTemplArgs;
    
protected:
    std::array<T1, nTemplArgs> storage;
    
};

template <typename T1>
class Container<T1>
{
public:
    constexpr static int nTemplArgs = 1;
};




int main()
{
   Container<float, 5, 3, 7> cont;
   
   std::cout << cont.nTemplArgs;
}
