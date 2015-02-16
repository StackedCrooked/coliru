#include <type_traits>

template< class T >
typename std::add_rvalue_reference<T>::type declval();

struct T
{
    int foo();
};

decltype(declval<T>().foo()) foo = 42;

int main()
{
    
}