#include <cstddef>
#include <iostream>
#include <string>

#include<functional>

typedef int(*func1)(int);
typedef std::function<int(int)> func2;

int function(int)
{
    return 0;
}

template<typename F = func1>
int function1(F f = function)
{
    return 0;
}

template<typename F = func2>
int function2(F f = function)
{
    return 0;
}

template<typename F = func1>
int function3(F f = [](int i){return 0;})
{
    return 0;
}

template<typename F = func2>
int function4(F f = [](int i){return 0;})
{
    return 0;
}
