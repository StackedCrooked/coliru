#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

template <typename T1, int... Args>
class Container;

//template <int... Args>
//struct ArraySize;


template<int T1, int...Args>
struct ArraySize
{
    static const int SIZE = T1 * ArraySize<Args...>::SIZE;
};

template<int T1>
struct ArraySize<T1>
{
	static const int SIZE = T1;
};

template <typename T1, int dim, int... Args>
class Container<T1, dim, Args...>
{
public:
    Container() {}

    constexpr static int nTemplArgs = dim * ArraySize<Args...>::SIZE;
    
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
