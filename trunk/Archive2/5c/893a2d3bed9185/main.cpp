#include <type_traits>
#include <utility>

template<class T, class... TT>
std::initializer_list< typename std::decay<T>::type >
il(T&& p0, TT&&... ps)
{
    return { std::forward<T>(p0), std::forward<TT>(ps)... };
}

#include <iostream>

template<class T>
void print(T&& p)
{
    for(auto const& e : p) std::cout << e << ", ";
}

int main()
{
    print( il(1,2,3,4) );
    print( il(1.1,2.2,3.3,4.4) );
}