#include <map>

template< template<class> class X, class T0>
int comp(X<T0>) { return 1; }
template< template<class, class> class X, class T0, class T1>
int comp(X<T0, T1>) { return 2; }
template< template<class, class, class> class X, class T0, class T1, class T2>
int comp(X<T0, T1, T2>) { return 3; }
template< template<class, class, class, class> class X, class T0, class T1, class T2, class T3>
int comp(X<T0, T1, T2, T3>) { return 4; }

#include <iostream>

template< template<class...> class AssocContainer >
void foo()
{
    AssocContainer<int, int> x;
    std::cout << comp(x);
}

int main()
{
    foo<std::map>();
}