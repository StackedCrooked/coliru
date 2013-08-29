/*#include <iostream>
using namespace std;
template <class T> void f(const T& x)
{
        
        typedef T T1;
        typedef T** T2;
        typedef T**& T3;
typedef T T4 [2] [ 1 ] ;

        T1 x1 = x; // T1 is nullptr_t
        T1* x2 = &x1; // Can take address nullptr_t and x2 is nullptr_t*
        T2 x3 = &x2; // T2 is nullptr_t**
        T3 x4 = x3;  // T3 is nullptr_t**&( & is reference) and x4 is the reference of x3
        T4 x5 = {x, x1}; // x is nullptr and x5 is nullptr_t(*)[1][1]

        T1 x6 = static_cast<T1>(x); 
        T1* x7 = const_cast<T1*>(x2);
        T3 x8 = static_cast<T**&>(x4);
        T4* x9 = const_cast<T4*>(&x5);

        T1 x10 = x2 ? x : x1;
        x2 ? void(x) : (void)37;
}

int main()
{
        f(nullptr); // T - std::nullptr_t
        
        return 0;
}

typedef decltype(nullptr) nullptr_t;

nullptr_t&& f()
{
        return (nullptr_t&&)nullptr;
}
*/
/*
typedef decltype(nullptr) nullptr_t;

struct A {};

typedef void (A::*pmf)(void);

typedef const int A::*const pd;

void f()
{
        const_cast<void*>((const void*)nullptr);

        const_cast<A*>((const A*)nullptr);

        const_cast<int A::*>(pd(nullptr));
        
        nullptr_t x = nullptr;
        const_cast<nullptr_t&>(x);
        const_cast<nullptr_t&&>(x);
        const_cast<int&&>(3);
}
*/

typedef decltype(nullptr) nullptr_t;

struct A {
        operator nullptr_t()
        {
                return 0;
        }
};

typedef double A::*pd;

//pd x[] = {nullptr, x[1]};
//pd x[] = {nullptr,x[1]};
pd x[] = {x[0],x[1]};
int main()
{
        if (x[0] || x[1])
        {
                __builtin_printf("%d\n",x[0]);
                return 1;
        }
        return 0;
}
