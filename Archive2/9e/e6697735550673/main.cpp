#include <iostream>
#include <utility>

template<class T>
T& foo(T* p) { std::cout << "T*\n"; return *p; }

template<class T>
T&& foo(T&& p) { std::cout << "T&&\n"; return std::forward<T>(p); }

int main()
{
    int i;
    int const c = 42;
    
    foo(int{});
    foo(i);
    foo(&i);
    
    foo(c);
    foo(&c);
    
    int* p;
    foo(p);
}