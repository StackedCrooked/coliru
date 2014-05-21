#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>


template< typename... T >
struct RecursiveHelper
{
    typedef std::function< RecursiveHelper(T...) > type;
    RecursiveHelper( type f ) : func(f) {}
    operator type () { return func; }
    type func;
};

typedef RecursiveHelper<int&>::type callback_t;

callback_t f1(int & i)
{
    std::cout << "f1: i==" << i << std::endl;
    i++;
    return f1;
}
callback_t f0(int & i)
{
    std::cout << "f0: i==" << i << std::endl;
    if(i==0) i++;
    return f1;
}
callback_t start(int & i)
{
    std::cout << "start: i==" << i << std::endl;
    i=0;
    return f0;
}

int main()
{
    
    int i;  
    
    callback_t s = start;
    
    s = s(i);
    s = s(i);
    s = s(i);
    
    std::cout << "i==" << i << std::endl;
    
}


